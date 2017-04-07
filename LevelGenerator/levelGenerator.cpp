#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <time.h>
#include <algorithm>
#include <complex>
#include "Library/Point4.h"
#include "Library/Platform.h"
#include "Library/Library.h"
#include "Instance/Instance.h"
#include "Instance/PlatInstance.h"
#include "Instance/Position.h"
#include "Instance/Vec3.h"
#include "Polynome.h"
#include "levelGenerator.h"

using namespace std;

#define PI 3.14159265


// constantes globales
const int nbPointBezier = 6 ;
const long double G = 38.81;
const long double Vk = 75.0;
const Point4 Vitmin = Point4(140,140,85,2) ;
const Point4 Vitmax = Point4(140,140,85,2);
const long double EPSILON = 0.0001;
const long double probaPonctuelle = 0.1 ;
const long double LAST_T = 0.992;


// prototypes
bool triBezier(const Point4& a, const Point4& b, Point4 entree, Point4 sortie) ;
void generationLocale(const Library& bibli, Point4 entree, Point4 sortie, int largeur, int profondeur, int hauteur, Instance& karabonga) ;
void choixPlatforme(const Library& bibli, Point4 position, long double t, int& id, float& rotation, long double& t_fin, Point4& finPlat, Point4& acc, bool& ponctuelle) ;
Library subLibrary(Library const& bibli, Point4 entree, Point4 sortie) ;
Point4 bezierT(long double t) ;
Point4 royalT(long double t, long double coeff = 85) ;
Point4 arrivalJump(Point4 depart, Point4 direction, Point4 vitesse) ;
Point4 arrival(Point4 depart, Point4 vitesse, long double& t0) ;
long double findT (Point4 position, long double epsilon = EPSILON) ;
void ConstructionHeaviside(int largeur, int profondeur, int hauteur) ;
Point4 HeavT(long double t) ;


// global
Point4 pointBezier[nbPointBezier] ;
Polynome Bx, By, Bz, Bk ;


// On crée une discontinuité
vector<int> posHeav;
vector<Point4> decHeav;



bool triBezier(const Point4& a, const Point4& b, Point4 entree, Point4 sortie)
{
	// On projete A et B sur la ligne entree-sortie
	// Renvoie true si A est plus proche de l'entree que B
	if (scal2(a-entree, sortie-entree) < scal2(b-entree, sortie-entree))
		return true ;
	else
		return false ;
}




void generationLocale(const Library& bibli, Point4 entree, Point4 sortie, int largeur, int profondeur, int hauteur, Instance& karabonga)
{
	// input : liste de platformes, un rectangle avec entree et sortie
	// output : une liste d'instance de platformes (sauf entree et sortie)

	// largeur -> x ; profondeur -> y ; hauteur -> z




	int** pasc = (int**) malloc((nbPointBezier+1)*sizeof(int*)) ;
	for (int i = 0 ; i <= nbPointBezier ; i++) {
		pasc[i] = (int*) malloc((i+1)*sizeof(int)) ;
		pasc[i][0] = 1 ;
		pasc[i][i] = 1 ;
	}
	for (int i = 1 ; i <= nbPointBezier ; i++) {
		for (int j = 1 ; j < i ; j++) {
			pasc[i][j] = pasc[i-1][j-1] + pasc[i-1][j] ;
		}
	}

	// Pt Bezier temporaires
	Point4 temp ;
	vector<Point4> tempBezier ;
	for(int i=1 ; i<nbPointBezier-1 ; i++) {
		temp = Point4(rand() % largeur,rand() % profondeur,rand() % hauteur, rand() % 5000) ;
		if (scal2(temp-entree, sortie-entree)<0||scal2(temp-entree, sortie-entree)>pow(dist2(entree,sortie),2))
			i--;
		else
			tempBezier.push_back(temp) ;
		// 5000 pour que le baryncentre se passe bien pour une dimension torique, on repasse plus tard entre  0 et 1000.
	}

	// tri
	pointBezier[0] = entree ;
	sort(tempBezier.begin(), tempBezier.end(), bind(triBezier,placeholders::_1,placeholders::_2,entree,sortie));
	for(int i=1 ; i<nbPointBezier-1 ; i++) {
		pointBezier[i] = tempBezier[i-1] ;
	}
	pointBezier[nbPointBezier-1] = sortie ;

	//// Ecartement pour remplir le pave (peut theoriquement fail... mais bon en pratique...)

	// min et max atteints par courbe actuelle
        
	long double minX=entree.getX(), maxX=entree.getX(), minY=entree.getY(), maxY=entree.getY(), minZ=entree.getZ(), maxZ=entree.getZ() ;
	//pas de 0.02 ok (50* ancien BezierT) ? faire avec polynomes (3*durandkerner + recalcul polynomes) ?
	for (int i = 1 ; i<=50 ; i++) {

		//ancien BezierT
		long double x=0,y=0,z=0,k=0 ;
		long double t = i*1.0/50 ;
		for (int j = 0; j < nbPointBezier ; j++) {
			long double coef = pasc[nbPointBezier-1][j]*pow(t,j)*pow(1-t,nbPointBezier-j-1) ;
			x += coef * pointBezier[j].getX() ;
			y += coef * pointBezier[j].getY() ;
			z += coef * pointBezier[j].getZ() ;
			k += coef * pointBezier[j].getK() ;
		}
		minX = min(minX,x) ;
		maxX = max(maxX,x) ;
		minY = min(minY,y) ;
		maxY = max(maxY,y) ;
		minZ = min(minZ,z) ;
		maxZ = max(maxZ,z) ;

	}

	//ratio d'ecartement (laisse 0.05 de marge de chaque cote)

	long double resizeX = 0.9*largeur/(maxX - minX) ;
	long double resizeY = 0.9*profondeur/(maxY - minY) ;
	long double resizeZ = 0.9*hauteur/(maxZ - minZ) ;

	//ecartement

	for (int i = 1; i < nbPointBezier-1 ; i++) {
		Point4 temp = pointBezier[i] ;
		int x = temp.getX() , y = temp.getY() , z = temp.getZ() , k = temp.getK() ;
		pointBezier[i] =   Point4((x-minX+0.05*largeur)*resizeX, (y-minY+0.05*profondeur)*resizeY, (z-minZ+0.05*hauteur)*resizeZ, k) ;
	}


	/*
	 // utilise comme demo en mi-rendu
	 pointBezier[0] = entree ;
	 pointBezier[1] = Point4(2000,25000,2500,800) ;
	 pointBezier[2] = Point4(4000,15000,-1100,100) ;
	 pointBezier[3] = Point4(6000,-15000,2500,800) ;
	 pointBezier[4] = Point4(8000,25000,-200,-100) ;
	 pointBezier[nbPointBezier-1] = sortie ;
	 */

	//// Calcul des polynomes de Bezier

	vector<long double> Vx, Vy, Vz, Vk ;
	Vx.resize(nbPointBezier+1) ;
	Vy.resize(nbPointBezier+1) ;
	Vz.resize(nbPointBezier+1) ;
	Vk.resize(nbPointBezier+1) ;
	for (int i = 0 ; i <= nbPointBezier ; i++) {
		Vx[i] = 0 ;
		Vy[i] = 0 ;
		Vz[i] = 0 ;
		Vk[i] = 0 ;
	}
	for (int i = 0 ; i < nbPointBezier ; i++) {
		for (int j = 0 ; j < nbPointBezier-i ; j++) {
			int temp = pasc[nbPointBezier-1][i] * pasc[nbPointBezier-1-i][j] * pow(-1,j);
			Vx[i+j] += temp * pointBezier[i].getX() ;
			Vy[i+j] += temp * pointBezier[i].getY() ;
			Vz[i+j] += temp * pointBezier[i].getZ() ;
			Vk[i+j] += temp * pointBezier[i].getK() ;
		}
	}
	Bx = Vx ;
	By = Vy ;
	Bz = Vz ;
	Bk = Vk ;


	for (int i = 0 ; i <= nbPointBezier ; i++)
		free(pasc[i]) ;
	free(pasc) ;
        
        //for (float tt=0.0;tt<1;tt+=0.01)
          //  cout<<royalT(tt).getX()<<endl<<royalT(tt).getZ()<<endl;
     
	//ConstructionHeaviside(largeur, profondeur, hauteur);

	// reduire la librairie ?
	//Library lib = subLibrary(bibli, entree, sortie) ;


	//Instance karabonga ; // contiendra la liste des instance de platformes
	long double t = 0.0 ; // parametre actuel (suppose)
	Point4 position = entree ; // position actuelle
	Point4 vitesse = Vitmin ; // vitesse actuelle
        
	Point4 acceleration;
	long double diminution = 0.2;
        PlatInstance* pi ;
        bool ponctuelle = true;
	bool firstplat = true ;
        
        vector<Platform *> vectAscen ;
	bibli.select(bind(f_ascen,placeholders::_1,hauteur),vectAscen) ;

	while(t<1.0){

		Point4 debutplat = arrival(position, vitesse+acceleration, t) ; // debut platforme suivante (modifie t)
		vitesse = bound(vitesse+Point4(2,2,2,2),Vitmin,Vitmax) ; // vitesse pour la platforme suivante (pifometre ?)

                if (!firstplat && ponctuelle) {
                        int x1=position.getX(), y1=position.getY() ; // position plateforme ponctuelle
                        int x2=debutplat.getX(), y2=debutplat.getY() ; // debut plat suivante
                        int dx = x2-x1, dy = y2-y1 ;
                        float rot = atan2(dy,dx)*180/PI ;
                        pi->rotate(Vec3<float>(0,0,rot)) ;
                        karabonga.addPlatform(*pi) ;
                }
                else
                        firstplat = false ;

		position = debutplat ;

		int id ;
		float rotation ;
		long double t_fin ;
		Point4 finPlat ;
		Point4 acc;
                
                //ascenseur si necessaire
                Polynome Dx = derive(Bx), Dy = derive(By), Dz = derive(Bz) ;
                long double dx = Dx.evalreel(t), dy = Dy.evalreel(t), dz = Dz.evalreel(t) ;
                long double pente = dz / sqrt(dx*dx+dy*dy) ;
                if (pente > 3 && (int)vectAscen.size() > 0 && t < LAST_T) {
                    Platform* PF = vectAscen[0] ;
                    id = PF->getID() ;
                    acc = PF->getAddAcceleration();
                    rotation = 0.0 ;
                    ponctuelle = false ;
                    long double t0 ;
                    for (t0 = t ; t0 < LAST_T && pente > 2.5 ; t0 += 0.005) {
                        dx = Dx.evalreel(t), dy = Dy.evalreel(t), dz = Dz.evalreel(t) ;
                        pente = dz / sqrt(dx*dx+dy*dy) ;
                    }
                    finPlat = position + Point4(0,0,royalT(t0).getZ()-position.getZ(),100) ;
                    t_fin = findT(t) ;
                }
                else // choix normal
                    choixPlatforme(bibli, position, t, id, rotation, t_fin, finPlat, acc, ponctuelle) ;
                
                acc = Point4(acc.getX()*4,acc.getY()*4,acc.getZ()*4,acc.getK()*4);
		if (ponctuelle) {
			rotation=0 ;
			finPlat = position ;
		}
		else {
			t = t_fin ;
		}

		int x = position.getX() , y = position.getY(), z = position.getZ() , k = position.getK() ;
                cerr << "plat : " << x << " " << y  << " " << z << " " << k << endl ;
		Position pos = Position(k, // entree 4D
								Vec3<float>(x,y,z),// position d'entree
								Vec3<float>(0.0,0.0,rotation), // rotation
								Vec3<float>(1.0,1.0,1.0)) ;  // scale

		vector<Vec3<float>> posSortie ; // position de la sortie (on en met qu'une ?)
		vector<float> sortie4D ;
		vector<Position> pos4D ;

		if (! ponctuelle) {
			// sortie donne relatif a la platforme, donc doit inverser la rotation
                        //cerr << "debut gestion longue : " << position << "  " << finPlat << "  " << rotation << endl ;
                        int xtemp = finPlat.getX()-position.getX() , ytemp = finPlat.getY()-position.getY() ;
			long double r = sqrt(xtemp*xtemp+ytemp*ytemp) ;
			long double theta = atan2(ytemp,xtemp) *180/PI ;
			long double theta2 = theta - rotation*1.0 ;
			long double x2 = r*cos(theta2*PI/180) ;
			long double y2 = r*sin(theta2*PI/180) ;
                        if(abs(y2)<EPSILON)
                            y2 = 0 ;
                        //cerr << "fin gestion longue : " << x2 << "  " << y2 << endl ;
			posSortie.push_back(Vec3<float>(x2,y2,(float)finPlat.getZ())) ;
			sortie4D.push_back((float)finPlat.getK()) ;
                        // pos4D parce que voila...
                        pos4D.push_back(pos) ;
		}
		else {
                        // pos4D pour faire apparaitre et disparaitre dans la 4D
                        Position pos1 = Position((k-350+1000)%1000, // debut apparition
								Vec3<float>(x,y,z),
								Vec3<float>(0.0,0.0,0.0),
								Vec3<float>(0.0,0.0,0.0)) ;
                        Position pos2 = Position((k-180+1000)%1000, // fin appartition, debut plein
								Vec3<float>(x,y,z),
								Vec3<float>(0.0,0.0,0.0),
								Vec3<float>(1.0,1.0,1.0)) ;
                        Position pos3 = Position((k+180+1000)%1000, // fin plein, debut disparition
								Vec3<float>(x,y,z),
								Vec3<float>(0.0,0.0,0.0),
								Vec3<float>(1.0,1.0,1.0)) ;
                        Position pos4 = Position((k+350+1000)%1000, // disparu
								Vec3<float>(x,y,z),
								Vec3<float>(0.0,0.0,0.0),
								Vec3<float>(0.0,0.0,0.0)) ;
                        pos4D.push_back(pos1) ;
                        pos4D.push_back(pos2) ;
                        pos4D.push_back(pos3) ;
                        pos4D.push_back(pos4) ;
                }

		pi = new PlatInstance(id,pos,posSortie,sortie4D,pos4D,rand()) ;
                if (! ponctuelle) {
                        karabonga.addPlatform(*pi) ;
                }
		acceleration = Point4 (int(acceleration.getX()*diminution), int(acceleration.getY()*diminution), int(acceleration.getZ()*diminution), int(acceleration.getK()*diminution));
		acceleration = acceleration+acc;
		position = finPlat ;
	}

        if (ponctuelle) {
                int x1=position.getX(), y1=position.getY() ; // position derniere plateforme
                int x2=sortie.getX(), y2=sortie.getY() ; // position de fin
                int dx = x2-x1, dy = y2-y1 ;
                float rot = atan2(dy,dx)*180/PI ;
                pi->rotate(Vec3<float>(0,0,rot)) ;
                if (t<0.1)
                    karabonga.addPlatform(*pi) ;
        }

	//posttraitement


	//return karabonga ;

}

void ConstructionHeaviside(int largeur, int profondeur, int hauteur){
	//Pour effectuer les décalages sur x et y ont doit supposer que cela n'interfere pas ave les plateformes existantes
	// Pour cela on essaye de dévier à la perpendiculaire (à peu près...)
	for (int i = 0 ; i<4 ; i++){
		long double t1 = (float)rand()/(float)RAND_MAX;
		long double t2 = (float)rand()/(float)RAND_MAX;
		if (t1>t2){
			long double t3 = t1;
			t1 = t2;
			t2 = t3;
		}
		int espace = largeur;
		if (profondeur < espace)
			espace = profondeur;
		if (hauteur < espace)
			espace = hauteur;
		Point4 Postemp;
		for (long double t3 = t1; t3<t2;t3+=0.001){
			Postemp = royalT(t3);
			if (Postemp.getX()<espace)
				espace = Postemp.getX();
			if (largeur - Postemp.getX()<espace)
				espace = largeur - Postemp.getX();
			if (Postemp.getY()<espace)
				espace = Postemp.getY();
			if (profondeur - Postemp.getY()<espace)
				espace = profondeur - Postemp.getY();
			if (Postemp.getZ()<espace)
				espace = Postemp.getZ();
			if (hauteur - Postemp.getZ()<espace)
				espace = hauteur - Postemp.getZ();
		}
		if (espace > 0){
			long double decalh = rand()%4;
			long double decalz = rand()%10;
			long double Normalisation = decalh + decalz;
			long double borne1 = ((((float)rand()/(float)RAND_MAX)/3)+0.5)*espace;
			long double borne2 = (Vitmin.getZ()*Vitmin.getZ()/G*2)*(((float)rand()/(float)RAND_MAX)*4+2.5);
			if (borne2<borne1)
				borne1 = borne2;
			Polynome Dx = derive(Bx) , Dy = derive(By);
			long double dx = Dx.evalreel(t1), dy = Dy.evalreel(t1);
			long double dirx,diry; // On cherche à prendre un vecteur othogonal
			if (dy > 0.1 || dy < -0.1){
				dirx = 1;
				diry = - (dx/dy);
			}
			else{
				dirx = 0;
				diry = 1;
			}
			dirx = dirx/(dirx+diry);
			diry = diry/(dirx+diry);
			dx = Dx.evalreel(t2);
			dy = Dy.evalreel(t2);
			long double prodscal = dirx*dx+diry*dy;
			if (prodscal<0.3 && prodscal>-0.3){
				dirx+= (((float)rand()/(float)RAND_MAX)/3)-0.15;
				diry+= (((float)rand()/(float)RAND_MAX)/3)-0.15;
				dirx = dirx/(dirx+diry);
				diry = diry/(dirx+diry);
				int signh = 1, signz = 1;
				if (((float)rand()/(float)RAND_MAX)<0.5)
					signh = -1;
				if (((float)rand()/(float)RAND_MAX)<0.5)
					signz = -1;
				decHeav.push_back(Point4(signh*int(Normalisation*dirx*borne1*decalh+0.5),signh*int(Normalisation*diry*borne1*decalh+0.5),signz*int(Normalisation*borne1*decalz+0.5),0));
				posHeav.push_back(t1);
				posHeav.push_back(t2);
			}
			else{
				if(((float)rand()/(float)RAND_MAX)<0.7){
					i--;
				}
			}
		}
		else{
			if(((float)rand()/(float)RAND_MAX)<0.7){
				i--;
			}
		}
	}

}

Point4 HeavT(long double t){
	Point4 Heav = Point4(0,0,0,0);
	for (unsigned int i = 0; i< decHeav.size();i++){
		if (posHeav[2*i]<t && t<posHeav[2*i+1]){
			Heav = Heav + decHeav[i];
		}
	}
	return Heav;
}

void choixPlatforme(const Library& bibli, Point4 position, long double t, int& id, float& rotation, long double& t_fin, Point4& finPlat, Point4& acc, bool& ponctuelle)
{
	// choisi la prochaine platforme a utiliser
	// warning : id, rotation, t_fin, finPlat, acc sont modifiés
	// input : bibli, position de debut de platforme, avec parametre estime t, + parametres modifiables
	// output : booleen true si platforme ponctuelle, les autres informations seront dans les parametres modifiés


	if (!ponctuelle || (((float)rand()/(float)RAND_MAX)<probaPonctuelle)||t > LAST_T) { // proba de base
		ponctuelle = true ;
	}

	else {
            //cerr << "tentative platforme longue" << endl ;
		// calculs de derivees, donnant la direction locale
		long double hsaut = Vitmin.norm2()*2*Vitmin.getZ()/G ;
		Polynome Dx = derive(Bx) , Dy = derive(By) , Dz = derive(Bz) , Dk = derive(Bk) ;
		long double dx = Dx.evalreel(t), dy = Dy.evalreel(t), dz = Dz.evalreel(t), dk = Dk.evalreel(t) ;
		long double d = sqrt(dx*dx+dy*dy+dz*dz) ;
		vector<Platform *> temp ;
		for (int i = 0 ; i<5 && temp.size()==0 ; i++) {
			long double h = ((float)rand()/(float)RAND_MAX*3+2)*hsaut ;
			long double x=dx*h/d,y=dy*h/d,z=dz*h/d,k=dk*h/d ;
			Point4 finPlat1 = Point4(int(x+0.5),int(y+0.5),int(z+0.5),int(k+0.5)) + position ; // on part un peu loin en direction de la derivee
			t_fin = findT(finPlat1) ; // on revient sur la courbe
			if (t_fin > LAST_T)
				t_fin = LAST_T;
			finPlat = royalT(t_fin) ; // Point4 de fin de platforme souhaite
			bibli.select(bind(f_atteintPoint,placeholders::_1,finPlat-position),temp) ; // platformes pouvant atteindre le point souhaite
                        //cerr << "dk : " << finPlat.getK()-position.getK() << endl ;
                        //cerr << "i : " << i << endl ;
		}

		if (temp.size()!=0) {
                        //cerr << "reussite platforme longue" << endl ;
                        ponctuelle = false ;
			// on recupere une platformes random parmis celle possibles
			int poidstotal = 0 ;
			for(unsigned int k=0 ; k<temp.size() ; k++){
				poidstotal += (temp[k])->getApparitionWeight()+1 ;
			}
			int r = rand() % poidstotal ;
			int k = 0 ;
			while (temp[k]->getApparitionWeight()+1 <= r) {
				r=r-temp[k]->getApparitionWeight()-1 ;
				k++ ;
			}

			Platform* PF = temp[k] ;
			id = PF->getID() ; // recupere ID
			acc = PF->getAddAcceleration();
			rotation = 0.0 ;
			// on calcul la rotation necessaire
                        Point4 dir = finPlat-position ;
                        int i = 0 ;
                        while (!f_atteintPointViaI(*PF, dir, i))
                            ++i ;
                        long double x = dir.getX() ;
                        long double y = dir.getY() ;
                        double rad = sqrt(x*x+y*y) ;
                        long double theta = atan2(y,x)*180/PI ;
                        Point4 pmin = PF->getSortieMin()[i] ;
                        Point4 pmax = PF->getSortieMax()[i] ;
                        int xmin=pmin.getX(), ymin=pmin.getY(), xmax=pmax.getX(), ymax=pmax.getY() ;
                        if (ymin <= 0 && 0 <= ymax && xmin <= rad && rad <= xmax) { // cas ou la plateforme est, de base, dirigee vers x croissant
                            rotation = theta ;
                        }
                        else { // calculs compliques probablement jamais utilises
                            // arccos dans [0;PI], arcsin dans [-PI/2;PI/2]
                            long double rotx_min = 180/PI*acos(min(1.0,xmax/rad)) ;
                            long double rotx_max = 180/PI*acos(max(-1.0,xmin/rad)) ;
                            long double roty_min = 180/PI*asin(max(-1.0,ymin/rad)) ;
                            long double roty_max = 180/PI*asin(min(1.0,ymax/rad)) ;
                            if (rotx_min <= roty_max && roty_min <= rotx_max) { // 1er quart
                                long double rot_min = max(rotx_min, roty_min) ;
                                long double rot_max = min(rotx_max, roty_max) ;
                                long double rot_platforme = rot_min+rot_max/2 ;
                                rotation = theta - rot_platforme ;
                            }
                            else if (rotx_min <= 180-roty_min && 180-roty_max <= rotx_max) { // 2eme quart
                                long double rot_min = max(rotx_min, 180-roty_max) ;
                                long double rot_max = min(rotx_max, 180-roty_min) ;
                                long double rot_platforme = rot_min+rot_max/2 ;
                                rotation = theta - rot_platforme ;
                            }
                            else if (360-rotx_max <= 180-roty_min && 180-roty_max <= 360-rotx_min) { // 3eme quart
                                long double rot_min = max(360-rotx_max, 180-roty_max) ;
                                long double rot_max = min(360-rotx_min, 180-roty_min) ;
                                long double rot_platforme = rot_min+rot_max/2 ;
                                rotation = theta - rot_platforme ;
                            }
                            else if (360-rotx_max <= 360+roty_max && 360+roty_min <= 360-rotx_min) { // 4eme quart
                                long double rot_min = max(360-rotx_max, 360+roty_min) ;
                                long double rot_max = min(360-rotx_min, 360+roty_max) ;
                                long double rot_platforme = rot_min+rot_max/2 ;
                                rotation = theta - rot_platforme ;
                            }
                            else { // pas de rotation qui marche... watt ?
                                exit(333) ;
                            }
                        }
		}
		else { // si on n'arrive pas a mettre en place une platforme longue
			ponctuelle = true ;
		}
	}

	if (ponctuelle) {
		// on recupere une platforme ponctuelle aleatoirement
		vector<Platform *> temp ;
		bibli.select(f_ponctuelle,temp) ;
		if (temp.size()==0) // pas de platforme ponctuelle dans la librairie ? serieux ?
			exit(144) ;
		int poidstotal = 0 ;
		for(unsigned int k=0 ; k<temp.size() ; k++){
			poidstotal += (temp[k])->getApparitionWeight()+1 ;
		}
		int r = rand() % poidstotal ;
		int k = 0 ;
		while (temp[k]->getApparitionWeight()+1 <= r) {
			r=r-temp[k]->getApparitionWeight()-1 ;
			k++ ;
		}
		id = temp[k]->getID() ; // recupere ID
		acc = temp[k]->getAddAcceleration();
	}

	
}


Library subLibrary(Library const& bibli, Point4 entree, Point4 sortie)
{
	// choisi 8 plateformes dans la librairie, permet d'eviter les sous-niveaux trop heterogenes
	// a reecrire (fct f_monte etc.)

	int nbMonte = 1 ;
	int nbPlat = 4 ;
	int nbDescend = 1 ;
	int x ;
	Point4 normse = sortie - entree;
	long double l = normse.norm3();
	long double z = normse.getZ() ;
	long double sinus = z/l;

	if (sinus >= 0.5) {
		nbMonte += 2 ;
	}
	else if (sinus >= 0.25) {
		nbMonte += 1 ;
		nbPlat += 1 ;
	}
	else if (sinus >= -0.25) {
		nbPlat += 2 ;
	}
	else if (sinus >= -0.5) {
		nbDescend += 1 ;
		nbPlat +=1 ;
	}
	else {
		nbDescend += 2 ;
	}

	Library ret = Library() ;
	vector<Platform *> temp ;

	bibli.select(f_monte,temp) ;
	if (temp.size()==0)
		bibli.select(f_true,temp) ;
	for (int i=0 ; i<nbMonte ; i++) {
		x = rand() % temp.size() ;
		ret.push(temp[x]) ;
	}

	temp.clear() ;
	bibli.select(f_plat,temp) ;
	if (temp.size()==0)
		bibli.select(f_true,temp) ;
	for (int i=0 ; i<nbPlat ; i++) {
		x = rand() % temp.size() ;
		ret.push(temp[x]) ;
	}

	temp.clear() ;
	bibli.select(f_descend,temp) ;
	if (temp.size()==0)
		bibli.select(f_true,temp) ;
	for (int i=0 ; i<nbDescend ; i++) {
		x = rand() % temp.size() ;
		ret.push(temp[x]) ;
	}

	return ret ;
}


Point4 bezierT(long double t)
{
	// renvoie le point de la courbe de Bezier de parametre t
	long double x=Bx.evalreel(t),y=By.evalreel(t),z=Bz.evalreel(t),k=Bk.evalreel(t) ;
	return Point4(int(x+0.5),int(y+0.5),int(z+0.5),int(k+0.5)%1000) ;
}


Point4 royalT(long double t,long double coef)
{
	// renvoie le point de la courbe royale de parametre t
	long double x=Bx.evalreel(t),y=By.evalreel(t),z=Bz.evalreel(t),k=Bk.evalreel(t) ;
        Polynome Dx = derive(Bx) , Dy = derive(By);
	long double dx = Dx.evalreel(t), dy = Dy.evalreel(t);
	long double dirx,diry; // On cherche à prendre un vecteur othogonal
	if (dy > 0.1 || dy < -0.1){
            dirx = 1;
            diry = - (dx/dy);
	}
        else{
            dirx = 0;
            diry = 1;
	}
        dirx = 1;
        diry = -(dx/dy);
        long double Znorm = dirx+abs(diry);
	dirx = dirx/Znorm;
        diry = diry/Znorm;
	x+=dirx*coef*sin(t*241);
	y+=diry*coef*sin(t*108);
	z+=0.2*coef*sin(t*107);
	return Point4(int(x+0.5),int(y+0.5),int(z+0.5),int(k+0.5)%1000) ;
}


Point4 arrivalJump(Point4 depart, Point4 direction, Point4 vitesse)
{
	// fonction utilisee par la fonction arrival
	// renvoie le point correspondant au debut de la prochaine platforme, avec pour objectif un point que l'on espere valide mais faisant les corrections pour satisfaire la physique et la vitesse

	direction = direction - depart;
	long double x = direction.getX();
	long double y = direction.getY();
	long double x2 = sqrt(x*x+y*y);
	long double cosa = x / x2;
	long double sina = y / x2;
	long double vh = sqrt(vitesse.getX()*vitesse.getX()+vitesse.getY()*vitesse.getY());
	//Mettre une erreur si vh = 0
	long double vz = vitesse.getZ();
	long double t = x2/vh;
	long double z = (t*vz)-(t*t*G)/(2);
	if (floor(z)>direction.getZ()){
		if (direction.getK()>0){
			if (Vk*t>direction.getK()){
				direction = direction + depart;
				return Point4(direction.getX(),direction.getY(),direction.getZ(),direction.getK());
			}
			else{
				direction = direction + depart;
				return Point4(direction.getX(),direction.getY(),direction.getZ(),depart.getK()+int(Vk*t));
			}
		}
		else{
			if (-Vk*t<direction.getK()){
				direction = direction + depart;
				return Point4(direction.getX(),direction.getY(),direction.getZ(),direction.getK());
			}
			else{
				direction = direction + depart;
				return Point4(direction.getX(),direction.getY(),direction.getZ(),depart.getK()-int(Vk*t));
			}
		}
	}
	else{
		z = direction.getZ();
		if (z>=vz*vz/(2*G)){
			//cas où on est au-dessus du maxima de la cloche :
			// Donc sous-niveau probablement trop pentu choisir quoi renvoyer :
			//Pour le moment on renvoie le sommet de la cloche :
                        //cerr << "cas pas cool" << endl ;
			long double zmax = vz*vz/(2*G)+depart.getZ();
			t = vz/G;
			if (abs(Vk*t)>abs(direction.getK())){
				return Point4(int(depart.getX()+vh*t/x2*direction.getX()),int(depart.getY()+vh*t/x2*direction.getY()),zmax,depart.getK()+direction.getK());
			}
			else{
				if (direction.getK()<0){
					return Point4(int(depart.getX()+vh*t/x2*direction.getX()),int(depart.getY()+vh*t/x2*direction.getY()),zmax,depart.getK()-int(Vk*t));
				}
				else{
					return Point4(int(depart.getX()+vh*t/x2*direction.getX()),int(depart.getY()+vh*t/x2*direction.getY()),zmax,depart.getK()+int(Vk*t));
				}
			}
		}
		else{
			//equation du secon degré ! Youpi !
			long double sqrtdelta = sqrt((4*vz*vz/(G*G))-8*z/G);
			long double t1 = ((2/G)*vz-sqrtdelta)/2;
			long double x21 = vh*t1;
			if (x21>x2){
                                //cerr << "cas trop proche" << endl ;
				if (abs(Vk*t1)>abs(direction.getK())){
					return Point4(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z+depart.getZ(),depart.getK()+direction.getK());
				}
				else{
					if (direction.getK()<0){
						return Point4(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z+depart.getZ(),depart.getK()-int(Vk*t1));
					}
					else{
						return Point4(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z+depart.getZ(),depart.getK()+int(Vk*t1));
					}
				}
			}
			else{
                                
                                //cerr << "cas trop loin" << endl ;
				long double t2 = ((2/G)*vz+sqrtdelta)/2;
				long double x22 = vh*t2;
				if (abs(Vk*t2)>abs(direction.getK())){
					return Point4(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z+depart.getZ(),depart.getK()+direction.getK());
				}
				else{
					if (direction.getK()<0){
						return Point4(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z+depart.getZ(),depart.getK()-int(Vk*t2));
					}
					else{
						return Point4(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z+depart.getZ(),depart.getK()+int(Vk*t2));
					}
				}
			}
		}
	}
}


Point4 arrival(Point4 depart, Point4 vitesse, long double& t0)
{
	// input : position actuelle de la generation (fin de platforme), proche du parametre t0 de la courbe royale, et vitesse possible du joueur
	// output : calcul le debut souhaité de la prochaine platforme, puis appelle arrivalJump
	// warning : modifie t0

	Point4 arrive ;
	long double t = 1.0;
	long double pas = t-t0 ;
	Point4 dirDestination ;
	long double vz = vitesse.getZ() ;
	// vz positive ?
	long double hmax = vitesse.norm2()*2*vz/G ;
	long double zmax = vz*vz/(2*G) ;
	bool cont = false ;
	while (! cont || pas > 0.0005) {
		dirDestination = royalT(t)-depart ;
		long double z = dirDestination.getZ() ;
		long double h = dirDestination.norm2() ;
		if (z>0.6*zmax||z<-0.9*zmax||h>0.85*hmax||h<-0.7*hmax) {   // distance suffisemment grande
			if (z>0.8*zmax||z<-2.0*zmax||h>0.95*hmax||h<-0.95*hmax) {   // distance trop grande
				pas = pas/2 ;
				t = t - pas ;
				//cout<<"z  "<<z<<"   "<<zmax<<endl;
				//cout<<"h  "<<h<<"   "<<hmax<<endl;
			}
			else {  // distance bien
				arrive = arrivalJump(depart,dirDestination+depart, vitesse) ;
				//cout<<"?"<<endl;
				cont = (dist3(arrive, depart)<=1500) ;
				if (! cont){
					pas = pas/2 ;
					t = t - pas ;
				}
				//cout<<dist3(arrive, depart)<<endl;
			}
		}
		else{   // distance pas assez grande
			if (t==1.0) { // fin de toute facon
				cont = true ;
			}
			else {
				pas = pas/2 ;
				t = t + pas ;
			}
		}
	}
	if (! cont){
		dirDestination = royalT(t)-depart ;
		long double z = dirDestination.getZ() ;
		long double h = dirDestination.norm2() ;
		if (! (z>0.6*zmax||z<-0.9*zmax||h>0.7*hmax||h<-0.7*hmax)){
			t+=2*pas;
			dirDestination = royalT(t)-depart ;
		}
	}
	t0 = t ;
	dirDestination = dirDestination+depart;
	//cout<<dirDestination.getX()<<"  "<<dirDestination.getY()<<"  "<<dirDestination.getZ()<<"  "<<dirDestination.getK()<<"  "<<endl;
	return arrivalJump(depart,dirDestination, vitesse);
}


long double findT (Point4 position, long double epsilon)
{
	// trouve t€[0,1] minimisant |B(t)-position|²

	Polynome Px, Py, Pz, D ;
	long double x=position.getX(), y=position.getY(), z=position.getZ() ;
	Px = Bx + Polynome(-x) ;
	Py = By + Polynome(-y) ;
	Pz = Bz + Polynome(-z) ;
	D = Px*Px + Py*Py + Pz*Pz ;

	vector<long double> extremum = derive(D).durandkerner(epsilon) ;
	extremum.push_back(0) ;
	extremum.push_back(1) ;
	int minindex = 0 ;
	long double distance = D.evalreel(extremum[0]) ;
	for (int i=1 ; i<int(extremum.size()) ; i++) {
		long double temp = D.evalreel(extremum[i]) ;
		if (temp<distance) {
			distance = temp ;
			minindex = i ;
		}
	}
	return extremum[minindex] ;
}
