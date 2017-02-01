#ifndef testPlatf_h
#define testPlatf_h

#include <vector>
#include <iostream>
#include "Point.h"

#define DEFAULT_WEIGHT 10


enum Forme {Cercle, DemiCercle, Triangle, Rectangle, Pentagone, Hexagone, Heptagone, Octogone} ;

class Platform{
private:
	//Attributs
	int ID; //Identifiant de la plateforme
	std::vector<Forme> formes; //Ensemble des formes pouvant être prises par la plateforme
	Point additiveAcceleration; //Modification d'accélération additive
	Point multiplicativeAcceleration; //Modification d'accelération multiplicative
	std::vector<Point> distSorties; //distance entre l'entree et chaque sortie
	std::vector<int> angleSorties; //angle entre l'entree et chaque sortie
	Point size; //taille du pavé Englobant de la platforme
	int apparitionWeight; //Poids d'apparition de la platforme (par défaut 10)
	bool reshapeAble; //Possibilité de déformer la plateforme
	
public:
	//Constructeurs
	Platform();
	Platform(std::istream &in);
	Platform(int ID,
			 std::vector<Forme>& formes,
			 Point& additiveAcceleration,
			 Point& multiplicativeAcceleration,
			 std::vector<Point>& distSorties,
			 std::vector<int>& angleSorties,
			 bool reshapeAble,
			 Point& size,
			 int apparitionWeight=DEFAULT_WEIGHT);
	
	//Getters
	int getID() const;
	int getNbFormes() const;
	const std::vector<Forme>& getFormes() const;
	const Point& getAddAcceleration() const;
	const Point& getCoeffAcceleration() const;
	int getNbSorties() const;
	const std::vector<Point>& getDistSorties() const;
	const std::vector<int>& getAngleSorties() const;
	bool getReshapeAble() const;
	
	~Platform();
};


#endif /* testPlatf_h */
