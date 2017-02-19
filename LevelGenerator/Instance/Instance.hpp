#ifndef Instance_hpp
#define Instance_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include <list>
#include "Position.hpp"
#include "PlatInstance.hpp"
#include "Vec3.hpp"

class Instance{
private:
	std::list<PlatInstance> plateformes;
	
public:
	Instance();
	
	/**
	 * Ajoute une plateforme dans l'instance.
	 * (Attention une fois ajoutée à l'instance une plateforme ne devient modifiable que par les fonctions de l'instance)
	 */
	void addPlatform(const PlatInstance& plat);
	
	/**
	 * Effectue une rotation de centre c et angles dr sur toute l'instance.
	 */
	void rotate(const Vec3<float>& c, const Vec3<float>& dr);
	
	/**
	 * Même fonction que la précédente mais ne nécessitant pas le calcul des sinus et cosinus si ils ont déjà été calculés.
	 */
	void rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz);
	
	/**
	 * Effectue une translation de vecteur d de toute l'instance.
	 */
	void translate(const Vec3<float>& d);
	
	/**
	 * Redimensionne toute l'instance.
	 */
	void rescale(const Vec3<float>& c,const Vec3<float>& ds);
	
	/**
	 * Opérateur d'addition d'instances.
	 * Ajoute à l'instance a toutes les plateformes de l'instance b.
	 * Attention b est vidé dans l'opération
	 * b ne dois pas être la même instance que a
	 */
	friend Instance& operator+=(Instance& a, Instance& b);
	
	friend std::ostream& operator<<(std::ostream& out, const Instance& i);
};

#endif /* Instance_hpp */
