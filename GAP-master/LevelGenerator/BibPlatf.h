
#ifndef BIBPLATF_H
#define BIBPLATF_H


#include "Point.h"
#include <iostream>

enum Forme {Cercle=1, DemiCercle, Triangle, Rectangle, Pentagone, Hexagone, Heptagone, Octogone} ;

class BibPlatf {
/// Cette classe défini les plateformes de la bibliothèque


public:
    BibPlatf();
    BibPlatf(int ID, int nbFormes, Forme* formes, int acceleration[4], int coeffAcceleration[4], int nbSorties, int* distSorties, int* angleSorties, bool peutChangerDeForme);
    
    int getID() const;
    int getNbFormes() const;
    Forme* getFormes() const;
    void getAcceleration(int tab[4]);
    void getCoeffAcceleration(int tab[4]);
    int getNbSorties() const;
    void getDistSorties(int* tab);
    void getAngleSorties(int* tab);
    bool getPeutChangerDeForme() const;
    
    virtual ~BibPlatf();
    
    
private:
    int m_ID ; // Numero interne de la bibliotheque
    int m_nbFormes ;
    Forme* m_formes ; // formes qui peuvent être prises par une instance de cette BibPlatf
    int m_acceleration[4] ; // Acceleration supplémentaire (type gravité), additive
    int m_coeffAcceleration[4] ; // Coefficient sur les actions du joueur (type frottements), multiplicative
    int m_nbSorties ;
    int* m_distSorties ; // distance entre l'entree et la sortie, pour nbSortie>=1
    int* m_angleSorties ; // angle entre l'entree et la sortie, pour nbSortie>=1
    bool m_peutChangerDeForme ;


};



#endif /* BIBPLATF_H */
