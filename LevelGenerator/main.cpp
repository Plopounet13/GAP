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
#include "Library/Point.h"
#include "Library/Platform.h"
#include "Library/Library.h"
#include "Instance/Instance.h"
#include "Instance/PlatInstance.h"
#include "Instance/Position.h"
#include "Instance/Vec3.h"
#include "Polynome.h"

using namespace std;

#define PI 3.14159265

// constantes globales
const int nbPointBezier = 6 ;
const long double G = 9.81;
const long double Vk = 100.0;
const Point Vitmin = Point(24,24,50,2) ;
const Point Vitmax = Point(36,36,50,8);
const long double EPSILON = 0.0001;
const long double probaPonctuelle = 0.6 ;
const long double LAST_T = 0.992;



// prototypes
bool triBezier(const Point& a, const Point& b, Point entree, Point sortie) ;
void generationLocale(const Library& bibli, Point entree, Point sortie, int largeur, int profondeur, int hauteur, Instance& karabonga) ;
bool choixPlatforme(const Library& bibli, Point position, long double t, int& id, int& rotation, long double& t_fin, Point& finPlat, Point& acc) ;
Library subLibrary(Library const& bibli, Point entree, Point sortie) ;
Point bezierT(long double t) ;
Point royalT(long double t, long double coeff = 84) ;
//bool accessibilite(int IDplatf, Point a, Point b) ;
Point arrivalJump(Point depart, Point direction, Point vitesse) ;
Point arrival(Point depart, Point vitesse, long double& t0) ;
long double findT (Point position, long double epsilon = EPSILON) ;
void ConstructionHeaviside(int largeur, int profondeur, int hauteur) ;
Point HeavT(long double t) ;


// global
Point pointBezier[nbPointBezier] ;
Polynome Bx, By, Bz, Bk ;

// On crée une discontinuité
vector<int> posHeav;
vector<Point> decHeav;

//srand (time(NULL)); à mettre quelquepart, ou autre seed

int main(int argc, char** argv)
{

    Library bibli ;


    filebuf fb;
    
    for(int i=0 ; i < 10 ; i++) {
        if (fb.open ("Library/p"+to_string(i)+".txt",ios::in))
        {
            istream is(&fb);
            Platform *p = new Platform(is) ;
            bibli.push(p) ;

            fb.close();
        }
        else {
            cout << "Failed" << endl ;
        }
    }



    Point entree = Point(100,100,20,200);
    Point sortie = Point(10000,10000,800,1600);
    Instance parcours;
    generationLocale(bibli, entree, sortie, 11000, 11000, 2000, parcours);
	cout << parcours << endl;

}


bool triBezier(const Point& a, const Point& b, Point entree, Point sortie)
{
        // On projete A et B sur la ligne entree-sortie
        // Renvoie true si A est plus proche de l'entree que B
    if (scal2(a-entree, sortie-entree) < scal2(b-entree, sortie-entree))
        return true ;
    else
        return false ;
}




void generationLocale(const Library& bibli, Point entree, Point sortie, int largeur, int profondeur, int hauteur, Instance& karabonga)
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
    Point temp ;
    vector<Point> tempBezier ;
    for(int i=1 ; i<nbPointBezier-1 ; i++) {
        temp = Point(rand() % largeur,rand() % profondeur,rand() % hauteur, rand() % 5000) ;
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
                long double t = i/50 ;
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
                Point temp = pointBezier[i] ;
                int x = temp.getX() , y = temp.getY() , z = temp.getZ() , k = temp.getK() ;
                pointBezier[i] =   Point((x-minX+0.05*largeur)*resizeX, (y-minY+0.05*profondeur)*resizeY, (z-minZ+0.05*hauteur)*resizeZ, k) ;
        }


    /*
    // utilise comme demo en mi-rendu
    pointBezier[0] = entree ;
    pointBezier[1] = Point(2000,25000,2500,800) ;
    pointBezier[2] = Point(4000,15000,-1100,100) ;
    pointBezier[3] = Point(6000,-15000,2500,800) ;
    pointBezier[4] = Point(8000,25000,-200,-100) ;
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

    ConstructionHeaviside(largeur, profondeur, hauteur);

    // reduire la librairie ?
    //Library lib = subLibrary(bibli, entree, sortie) ;


    //Instance karabonga ; // contiendra la liste des instance de platformes
    long double t = 0.0 ; // parametre actuel (suppose)
    Point position = entree ; // position actuelle
    Point vitesse = Vitmin ; // vitesse actuelle

    Point acceleration;
    long double diminution = 0.4;

    while(t<1.0){

        Point debutplat = arrival(position, vitesse+acceleration, t) ; // debut platforme suivante (modifie t)
        vitesse = bound(vitesse+Point(2,2,2,2),Vitmin,Vitmax) ; // vitesse pour la platforme suivante (pifometre ?)

        position = debutplat ;

        int id ;
        int rotation ;
        long double t_fin ;
        Point finPlat ;
        Point acc;
        bool ponctuelle = choixPlatforme(bibli, position, t, id, rotation, t_fin, finPlat, acc) ;

        if (ponctuelle) {
            rotation=0 ;
            finPlat = position ;
        }
        else {
            t = t_fin ;
        }

        int x = position.getX() , y = position.getY(), z = position.getZ() , k = position.getK() ;
        Position pos = Position(k, // entree 4D
                Vec3<float>(0.0,0.0,rotation), // rotation
                Vec3<float>(1.0,1.0,1.0), // scale
                Vec3<float>(x,y,z)) ; // position d'entree

        vector<Vec3<float>> posSortie ; // position de la sortie (on en met qu'une ?)
        vector<float> sortie4D ;

        if (! ponctuelle) {
            // donne relatif a la platforme, donc doit inverser la rotation
            int xtemp = finPlat.getX() , ytemp = finPlat.getY() ;
            long double r = sqrt(xtemp*xtemp+ytemp*ytemp) ;
            long double theta = atan2(ytemp,xtemp) *180/PI ;
            long double theta2 = theta - rotation*1.0 ;
            long double x2 = r*cos(theta2*PI/180) ;
            long double y2 = r*sin(theta2*PI/180) ;
            posSortie.push_back(Vec3<float>(x2,y2,(float)finPlat.getZ())) ;
            sortie4D.push_back((float)finPlat.getK()) ;
        }

        vector<Position> pos4D ;
        pos4D.push_back(pos) ;

        PlatInstance pi = PlatInstance(id,pos,posSortie,sortie4D,pos4D,rand()) ;
        acceleration = Point (int(acceleration.getX()*diminution), int(acceleration.getY()*diminution), int(acceleration.getZ()*diminution), int(acceleration.getK()*diminution));
        acceleration = acceleration+acc;
        karabonga.addPlatform(pi) ;
        //cout << "+1" << endl ;
        position = finPlat ;
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
        Point Postemp;
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
            if (dy < 0.1 && dy > -0.1){
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
                decHeav.push_back(Point(signh*int(Normalisation*dirx*borne1*decalh+0.5),signh*int(Normalisation*diry*borne1*decalh+0.5),signz*int(Normalisation*borne1*decalz+0.5),0));
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

Point HeavT(long double t){
    Point Heav = Point(0,0,0,0);
    for (unsigned int i = 0; i< decHeav.size();i++){
        if (posHeav[2*i]<t && t<posHeav[2*i+1]){
            Heav = Heav + decHeav[i];
        }
    }
    return Heav;
}

bool choixPlatforme(const Library& bibli, Point position, long double t, int& id, int& rotation, long double& t_fin, Point& finPlat, Point& acc)
{
    // choisi la prochaine platforme a utiliser
    // warning : id, rotation, t_fin, finPlat, acc sont modifiés
    // input : bibli, position de debut de platforme, avec parametre estime t, + parametres modifiables
    // output : booleen true si platforme ponctuelle, les autres informations seront dans les parametres modifiés

    bool ponctuelle ;

    if ((((float)rand()/(float)RAND_MAX)<probaPonctuelle)||t > LAST_T) { // proba de base
        ponctuelle = true ;
    }

    else {
        // calculs de derivees, donnant la direction locale
        long double hsaut = Vitmin.norm2()*2*Vitmin.getZ()/G ;
        Polynome Dx = derive(Bx) , Dy = derive(By) , Dz = derive(Bz) , Dk = derive(Bk) ;
        long double dx = Dx.evalreel(t), dy = Dy.evalreel(t), dz = Dz.evalreel(t), dk = Dk.evalreel(t) ;
        long double d = sqrt(dx*dx+dy*dy+dz*dz) ;
        vector<Platform *> temp ;
        for (int i = 0 ; i<5 && temp.size()==0 ; i++) {
            long double h = ((float)rand()/(float)RAND_MAX*5+3)*hsaut ;
            long double x=dx*h/d,y=dy*h/d,z=dz*h/d,k=dk*h/d ;
            Point finPlat1 = Point(int(x+0.5),int(y+0.5),int(z+0.5),int(k+0.5)) + position ; // on part un peu loin en direction de la derivee
            t_fin = findT(finPlat1) ; // on revient sur la courbe
            if (t_fin > LAST_T)
                t_fin = LAST_T;
            finPlat = royalT(t_fin) ; // Point de fin de platforme souhaite
            bibli.select(bind(f_atteintPoint,placeholders::_1,finPlat-position),temp) ; // platformes pouvant atteindre le point souhaite
        }

        if (temp.size()!=0) {
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
            rotation = 0 ;
            // on calcul la rotation necessaire
            while(! f_atteintPointRotation(*PF, finPlat-position, rotation)) {
                rotation += 10 ;
                // au pire rotation==350, sinon bug
                if (rotation==360)
                    exit(12) ;
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

    return ponctuelle ;
}


Library subLibrary(Library const& bibli, Point entree, Point sortie)
{
        // choisi 8 plateformes dans la librairie, permet d'eviter les sous-niveaux trop heterogenes
        // a reecrire (fct f_monte etc.)

    int nbMonte = 1 ;
    int nbPlat = 4 ;
    int nbDescend = 1 ;
    int x ;
    Point normse = sortie - entree;
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



Point bezierT(long double t)
{
        // renvoie le point de la courbe de Bezier de parametre t
    long double x=Bx.evalreel(t),y=By.evalreel(t),z=Bz.evalreel(t),k=Bk.evalreel(t) ;
    return Point(int(x+0.5),int(y+0.5),int(z+0.5),int(k+0.5)%1000) ;
}


Point royalT(long double t,long double coef)
{
        // renvoie le point de la courbe royale de parametre t
    long double x=Bx.evalreel(t),y=By.evalreel(t),z=Bz.evalreel(t),k=Bk.evalreel(t) ;
    x+=coef*sin(t*450);
    y+=coef*sin(t*501);
    z+=coef*sin(t*549);
    return Point(int(x+0.5),int(y+0.5),int(z+0.5),int(k+0.5)%1000)+HeavT(t) ;
}

/*
bool accessibilite(int IDplatf, Point a, Point b)
{
    // True si on peut sauter du point a de la platforme d'ID donnee au point b

    //1. aller cherche Platform d'id donnee, puis acceleration et coeffAcceleration

    //2. calculer vitesse max

    //3. courbe de mouvement

    //4. point dedans ?
    return true ;
}
*/

Point arrivalJump(Point depart, Point direction, Point vitesse)
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
                return Point(direction.getX(),direction.getY(),direction.getZ(),direction.getK());
            }
            else{
                direction = direction + depart;
                return Point(direction.getX(),direction.getY(),direction.getZ(),depart.getK()+int(Vk*t));
            }
        }
        else{
            if (-Vk*t<direction.getK()){
                direction = direction + depart;
                return Point(direction.getX(),direction.getY(),direction.getZ(),direction.getK());
            }
            else{
                direction = direction + depart;
                return Point(direction.getX(),direction.getY(),direction.getZ(),depart.getK()-int(Vk*t));
            }
        }
    }
    else{
        z = direction.getZ();
        if (z>=vz*vz/(2*G)){
            //cas où on est au-dessus du maxima de la cloche :
            // Donc sous-niveau probablement trop pentu choisir quoi renvoyer :
            //Pour le moment on renvoie le sommet de la cloche :
            long double zmax = vz*vz/(2*G)+depart.getZ();
            t = vz/G;
            if (abs(Vk*t)>abs(direction.getK())){
                return Point(int(depart.getX()+vh*t/x2*direction.getX()),int(depart.getY()+vh*t/x2*direction.getY()),zmax,depart.getK()+direction.getK());
            }
            else{
                if (direction.getK()<0){
                    return Point(int(depart.getX()+vh*t/x2*direction.getX()),int(depart.getY()+vh*t/x2*direction.getY()),zmax,depart.getK()-int(Vk*t));
                }
                else{
                    return Point(int(depart.getX()+vh*t/x2*direction.getX()),int(depart.getY()+vh*t/x2*direction.getY()),zmax,depart.getK()+int(Vk*t));
                }
            }
        }
        else{
            //equation du secon degré ! Youpi !
            long double sqrtdelta = sqrt((4*vz*vz/(G*G))-8*z/G);
            long double t1 = ((2/G)*vz-sqrtdelta)/2;
            long double x21 = vh*t1;
            if (x21>x2){
                if (abs(Vk*t1)>abs(direction.getK())){
                   return Point(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z+depart.getZ(),depart.getK()+direction.getK());
                }
                else{
                    if (direction.getK()<0){
                        return Point(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z+depart.getZ(),depart.getK()-int(Vk*t1));
                    }
                    else{
                        return Point(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z+depart.getZ(),depart.getK()+int(Vk*t1));
                    }
                }
            }
            else{
                long double t2 = ((2/G)*vz+sqrtdelta)/2;
                long double x22 = vh*t2;
                if (abs(Vk*t2)>abs(direction.getK())){
                   return Point(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z+depart.getZ(),depart.getK()+direction.getK());
                }
                else{
                    if (direction.getK()<0){
                        return Point(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z+depart.getZ(),depart.getK()-int(Vk*t2));
                    }
                    else{
                        return Point(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z+depart.getZ(),depart.getK()+int(Vk*t2));
                    }
                }
            }
        }
    }
}


Point arrival(Point depart, Point vitesse, long double& t0)
{
        // input : position actuelle de la generation (fin de platforme), proche du parametre t0 de la courbe royale, et vitesse possible du joueur
        // output : calcul le debut souhaité de la prochaine platforme, puis appelle arrivalJump
        // warning : modifie t0

        Point arrive ;
    long double t = 1.0;
    long double pas = t-t0 ;
    Point dirDestination ;
    long double vz = vitesse.getZ() ;
    // vz positive ?
    long double hmax = vitesse.norm2()*2*vz/G ;
    long double zmax = vz*vz/(2*G) ;
    bool cont = false ;
    while (! cont && pas > 0.001) {
        dirDestination = royalT(t)-depart ;
        long double z = dirDestination.getZ() ;
        long double h = dirDestination.norm2() ;
        if (z>0.6*zmax||z<-0.9*zmax||h>0.7*hmax||h<-0.7*hmax) {   // distance suffisemment grande
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


long double findT (Point position, long double epsilon)
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
