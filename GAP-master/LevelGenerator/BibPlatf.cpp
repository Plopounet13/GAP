#include "BibPlatf.h"


//// Focntions de la classe

BibPlatf::BibPlatf() : m_ID(0) {
}

BibPlatf::BibPlatf(int ID, int nbFormes, Forme* formes, int acceleration[4], int coeffAcceleration[4], int nbSorties, int* distSorties, int* angleSorties, bool peutChangerDeForme) : m_ID(ID) , m_nbFormes(nbFormes) , m_formes(formes) , m_nbSorties(nbSorties) , m_peutChangerDeForme(peutChangerDeForme)
{
    for (int i = 0 ; i<4 ; i++) {
        m_acceleration[i] = acceleration[i] ;
        m_coeffAcceleration[i] = coeffAcceleration[i] ;
    }
    for (int i = 0 ; i<m_nbSorties ; i++) {
        m_distSorties[i] = distSorties[i] ;
        m_angleSorties[i] = angleSorties[i] ;
    }
}


int BibPlatf::getID() const {
    return m_ID ;
}

int BibPlatf::getNbFormes() const {
    return m_nbFormes ;
}

Forme* BibPlatf::getFormes() const {
    return m_formes ;
}

void BibPlatf::getAcceleration(int tab[4]) {
    for(int i = 0 ; i<4 ; i++) {
        tab[i] = m_acceleration[i] ;
    }
}

void BibPlatf::getCoeffAcceleration(int tab[4]) {
    for(int i = 0 ; i<4 ; i++) {
        tab[i] = m_coeffAcceleration[i] ;
    }
}

int BibPlatf::getNbSorties() const {
    return m_nbSorties ;
}


void BibPlatf::getDistSorties(int* tab) {
    for(int i = 0 ; i<m_nbSorties ; i++) {
        tab[i] = m_distSorties[i] ;
    }
}

void BibPlatf::getAngleSorties(int* tab) {
    for(int i = 0 ; i<m_nbSorties ; i++) {
        tab[i] = m_angleSorties[i] ;
    }
}

bool BibPlatf::getPeutChangerDeForme() const {
    return m_peutChangerDeForme ;
}

BibPlatf::~BibPlatf() {
}



