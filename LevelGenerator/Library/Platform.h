#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>
#include <iostream>
#include "Point4.h"
#include "../Instance/Vec3.h"

#define DEFAULT_WEIGHT 10

class Platform{
private:
	//Attributs
	int ID; //Identifiant de la plateforme
	
	Point4 additiveAcceleration; //Modification d'accélération additive
	
	Point4 multiplicativeAcceleration; //Modification d'accelération multiplicative
	
	int apparitionWeight; //Poids d'apparition de la platforme (par défaut 10)
	
	Vec3<float> minScale; //Facteurs de scale min pour chaque dimension
	
	Vec3<float> maxScale; //Facteurs de scale max pour chaque dimension
	
	bool modifiable; //Possibilité de définir un comportement 4D pour la plateforme
	
	int nbSorties; //Nombre de sorties plaçable pour la plateforme
	
	//La sortie doit se trouver dans l'hyper pavé défini par sortieMin et sortieMax
	std::vector<Point4> sortieMin; //Position minimale d'une sortie
	
	std::vector<Point4> sortieMax; // Position maximale d'une sortie
	
	bool isTransition; // Est une plateforme inter sous-niveau
	
	Vec3<float> minRot; // Angles minimaux de rotation de la plateforme
	
	Vec3<float> maxRot; // Angles maximaux de rotation de la plateforme
	
	
public:
	//Constructeurs
	Platform();
	Platform(std::istream &in);
	
	//Getters
	int getID() const;
	const Point4& getAddAcceleration() const;
	const Point4& getCoeffAcceleration() const;
	int getApparitionWeight() const;
	int getNbSorties() const;
	const std::vector<Point4>& getSortieMin() const;
	const std::vector<Point4>& getSortieMax() const;
	const Vec3<float>& getMinScale() const;
	const Vec3<float>& getMaxScale() const;
	bool getModifiable() const;
	
	//Setters from stream
	void parse(std::istream &in);
	friend std::istream& operator>> (std::istream& in, Platform& p);
	
	~Platform();
};


#endif /* PLATFORM_H */
