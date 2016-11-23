
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



// prototypes
vector<Platf> generationLocale(BibPlatf* const& bibli, Point entree, Point sortie, Point coinRect, int largeur, int profondeur, int hauteur) ;
Point bezierT(Point* const& ptBez, vector<int> const& vpascal, float t) ;
bool accessibilite(int IDplatf, Point a, Point b) ;






//srand (time(NULL)); à mettre quelquepart, ou autre seed

int main(int argc, char** argv) {
    Point a = Point(5,8) ;
    Point b = Point(18,3,-5) ;
    cout << a << endl << b << endl << a+b << endl << dist3(a,b) ;
}







vector<Platf> generationLocale(BibPlatf* const& bibli, Point entree, Point sortie, Point coinRect, int largeur, int profondeur, int hauteur) {
    // hauteur -> z ; largeur -> x ; profondeur -> y
    
    vector<int> vpascal ;
    for (int i = 0 ; i < nbPointBezier ; i++) {
        vpascal.push_back(1);
        for (int j = i-1 ; j >0 ; j--) {
            vpascal[j] += vpascal[j-1] ;
        }
    }
    
    Point pointBezier[nbPointBezier] ;
    
    pointBezier[0] = entree ;
    for(int i=1 ; i<nbPointBezier-1 ; i++) {
        pointBezier[i] = Point(rand() % largeur,rand() % profondeur,rand() % hauteur, rand() % 5000) + coinRect ;
        // 5000 pour que le baryncentre se passe bien pour une dimension torique, on repasse plus tard entre  0 et 1000.
    }
    pointBezier[nbPointBezier] = sortie ;
    
    

    
    vector<Platf> plateformes ;
    

}


Point bezierT(Point* const& ptBez, vector<int> const& vpascal, float t) {
    float x=0,y=0,z=0,k=0 ;
    for (int i = 0; i < nbPointBezier ; i++) {
        float coef = vpascal[i]*pow(t,i)*pow(1-t,nbPointBezier-i) ;
        x += coef * ptBez[i].getX() ;
        y += coef * ptBez[i].getY() ;
        z += coef * ptBez[i].getZ() ;
        k += coef * ptBez[i].getK() ;
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