#ifndef LEVELGEN_H
#define LEVELGEN_H

#include "Library/Library.h"
#include "Library/Point4.h"
#include "Instance/Instance.h"

void generationLocale(const Library& bibli, Point4 entree, Point4 sortie, int largeur, int profondeur, int hauteur, Instance& outInst);

#endif /* LEVELGENERATOR_H */
