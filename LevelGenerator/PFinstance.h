#ifndef PFINSTANCE_H
#define PFINSTANCE_H


#include "Platform.h"
#include "Library.h"
#include "Point.h"
#include <iostream>

class PFinstance {
/// Cette classe défini les instances de plateformes


public:
    PFinstance();
    PFinstance(int type);
    int getType() const;
    // a completer
    virtual ~PFinstance();
    
    
private:
    int m_type ; // Numero de la BibPlatf source (ID)
    int m_nbPointPassage ;
    Point* m_positions ; // positions du centre de la plateforme pour chaque pt de passage
    int* m_echelles ; // scale de la platforme
    Point* m_angles ; // angles d'orientation, codés en entier (/!\ c'est pas vraiment un point)
    


};



#endif /* PFINSTANCE_H */
