
#ifndef PLATF_H
#define PLATF_H


#include "BibPlatf.h"
#include "Point.h"
#include <iostream>

class Platf {
/// Cette classe défini les instances de plateformes


public:
    Platf();
    Platf(int type);
    int getType() const;
    // a completer
    virtual ~Platf();
    
    
private:
    int m_type ; // Numero de la BibPlatf source (ID)
    int m_nbPointPassage ;
    Point* m_positions ; // positions du centre de la plateforme pour chaque pt de passage
    int* m_echelles ; // scale de la platforme
    Point* m_angles ; // angles d'orientation, codés en entier (/!\ c'est pas vraiment un point)
    


};



#endif /* PLATF_H */
