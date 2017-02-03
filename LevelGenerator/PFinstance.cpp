#include "PFinstance.h"


//// Focntions de la classe


PFinstance::PFinstance() : m_type(0) {}

PFinstance::PFinstance(int type) : m_type(type)
{}




int PFinstance::getType() const {
    return m_type ;
}

// a completer




PFinstance::~PFinstance() {
}



