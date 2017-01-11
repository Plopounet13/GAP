
//#include <iostream>
//#include <fstream>
#include <cstdlib>
//#include <stdlib.h>
//#include <string.h>
#include <cmath>
#include <vector>
#include <time.h>
#include "Point.h"
#include "BibPlatf.h"
#include "Platf.h"

using namespace std;


// constantes globales
const int nbPointBezier = 6 ;
const double G = 9.81;
const double Vk = 100.0;



// prototypes
vector<Platf> generationLocale(BibPlatf* const& bibli, Point entree, Point sortie, Point coinRect, int largeur, int profondeur, int hauteur) ;
Point bezierT(Point* const& ptBez, vector<int> const& vpascal, double t) ;
bool accessibilite(int IDplatf, Point a, Point b) ;
Point arrivalJump(Point depart, Point direction, Point vitesse) ;
Point arrival(Point depart, Point vitesse, double& t0) ;


// global
vector<int> vpascal ;
Point pointBezier[nbPointBezier] ;


//srand (time(NULL)); à mettre quelquepart, ou autre seed

int main(int argc, char** argv) {
    
    // Pascal
    for (int i = 0 ; i < nbPointBezier ; i++) {
        vpascal.push_back(1);
        for (int j = i-1 ; j >0 ; j--) {
            vpascal[j] += vpascal[j-1] ;
        }
    }
    
    
    Point a = Point(5,8) ;
    Point b = Point(18,3,-5) ;
    cout << a << endl << b << endl << a+b << endl << dist3(a,b) ;
}







vector<Platf> generationLocale(BibPlatf* const& bibli, Point entree, Point sortie, Point coinRect, int largeur, int profondeur, int hauteur) {
    // hauteur -> z ; largeur -> x ; profondeur -> y
    
    
    pointBezier[0] = entree ;
    for(int i=1 ; i<nbPointBezier-1 ; i++) {
        pointBezier[i] = Point(rand() % largeur,rand() % profondeur,rand() % hauteur, rand() % 5000) + coinRect ;
        // 5000 pour que le baryncentre se passe bien pour une dimension torique, on repasse plus tard entre  0 et 1000.
    }
    pointBezier[nbPointBezier] = sortie ;
    
    
    // TODO stuff
    
    vector<Platf> plateformes ;
    

}


Point bezierT(double t) {
    double x=0,y=0,z=0,k=0 ;
    for (int i = 0; i < nbPointBezier ; i++) {
        double coef = vpascal[i]*pow(t,i)*pow(1-t,nbPointBezier-i) ;
        x += coef * pointBezier[i].getX() ;
        y += coef * pointBezier[i].getY() ;
        z += coef * pointBezier[i].getZ() ;
        k += coef * pointBezier[i].getK() ;
    }
    return Point(int(x+0.5),int(y+0.5),int(z+0.5),int(k+0.5)%1000) ;
}


bool accessibilite(int IDplatf, Point a, Point b) {
    // True si on peut sauter du point a de la platforme d'ID donnee au point b

    //1. aller cherche BibPlatf d'id donnee, puis acceleration et coeffAcceleration

    //2. calculer vitesse max

    //3. courbe de mouvement

    //4. point dedans ?
    return true ;
}


Point arrivalJump(Point depart, Point direction, Point vitesse){
    direction = direction - depart;
    double x = direction.getX();
    double y = direction.getY();
    double x2 = sqrt(x*x+y*y);
    double cosa = x / x2;
    double sina = y / x2;
    double vh = sqrt(vitesse.getX()*vitesse.getX()+vitesse.getY()*vitesse.getY());
    //Mettre une erreur si vh = 0
    double vz = vitesse.getZ();
    double t = x2/vh;
    double z = (t*vz)-(t*t*G)/(2);
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
            double zmax = vz*vz/(2*G);
            t = vz/G;
            if (abs(Vk*t)>abs(direction.getK())){
                return Point(int(depart.getX()+vitesse.getX()*t),int(depart.getY()+vitesse.getY()*t),zmax,depart.getK()+direction.getK());
            }
            else{
                if (direction.getK()<0){
                    return Point(int(depart.getX()+vitesse.getX()*t),int(depart.getY()+vitesse.getY()*t),zmax,depart.getK()-int(Vk*t));
                }
                else{
                    return Point(int(depart.getX()+vitesse.getX()*t),int(depart.getY()+vitesse.getY()*t),zmax,depart.getK()+int(Vk*t));
                }
            }
        }
        else{
            //equation du secon degré ! Youpi !
            double sqrtdelta = sqrt((4*vz*vz/(G*G))-8*z/G);
            double t1 = (-(2/G)*vz-sqrtdelta)/2;
            double x21 = vh*t1;
            if (x21>x2){
                if (abs(Vk*t1)>abs(direction.getK())){
                   return Point(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z,depart.getK()+direction.getK());
                }
                else{
                    if (direction.getK()<0){
                        return Point(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z,depart.getK()-int(Vk*t1));
                    }
                    else{
                        return Point(int(depart.getX()+x21*cosa),int(depart.getY()+x21*sina),z,depart.getK()+int(Vk*t1));
                    }
                }
            }
            else{
                double t2 = (-(2/G)*vz+sqrtdelta)/2;
                double x22 = vh*t2;
                if (abs(Vk*t2)>abs(direction.getK())){
                   return Point(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z,depart.getK()+direction.getK());
                }
                else{
                    if (direction.getK()<0){
                        return Point(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z,depart.getK()-int(Vk*t2));
                    }
                    else{
                        return Point(int(depart.getX()+x22*cosa),int(depart.getY()+x22*sina),z,depart.getK()+int(Vk*t2));
                    }
                }
            }
        }
    }
}    


Point arrival(Point depart, Point vitesse, double& t0) {
    double t = 1.0;
    double pas = t-t0 ;
    Point dirDestination ;
    double vz = vitesse.getZ() ;
    // vz positive ?
    double hmax = vitesse.norm2()*2*vz/G ;
    double zmax = vz*vz/(2*G) ;
    bool cont = false ;
    while (not cont) {
        dirDestination = bezierT(t)-depart ;
        double z = dirDestination.getZ() ;
        double h = dirDestination.norm2() ;
        if (z>0.8*zmax or z<-0.9*zmax or h>0.8*hmax or h<-0.8*hmax) {   // distance suffisamment grande
            if (z>1.1*zmax or z<-2.0*zmax or h>1.1*hmax or h<-1.1*hmax) {   // distance trop grande
                pas = pas/2 ;
                t = t - pas ;
            }
            else {  // distance bien
                cont = true ;
            }
        }
        else{   // distance pas assez grande
            if (t==1) { // fin de toute facon
                cont = true ;
            }
            else {
                pas = pas/2 ;
                t = t + pas ;
            }
        }
    }
    t0 = t ;
    dirDestination=dirDestination+depart;
    return arrivalJump(depart,dirDestination, vitesse);
}




