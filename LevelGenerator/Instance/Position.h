#ifndef Position_h
#define Position_h

#include <vector>
#include <iostream>
#include <cmath>
#include "Vec3.h"

class Position{
	int k;
	Vec3<float> rot;
	Vec3<float> scale;
	Vec3<float> pos;
	
public:
	/**
	 * Getter retournant pos.
	 */
	const Vec3<float>& getPos() const;
	
	Position(const Vec3<float>& loc, const Vec3<float>& rot, const Vec3<float>& scale);
	Position(float k, const Vec3<float>& loc, const Vec3<float>& rot, const Vec3<float>& scale);
	Position(const Position& p);
	Position();
	
	/**
	 * Effectue une rotation d'angles dr centrée en pos.
	 */
	void rotate(const Vec3<float>& dr);
	
	/**
	 * Effectue une translation de vecteur d
	 */
	void translate(const Vec3<float>& d);
	
	/**
	 * Redimensionne selon les coefficients ds
	 */
	void rescale(const Vec3<float>& ds);
	
	/**
	 * Effectue une rotation de centre c et d'angles dr.
	 */
	void rotate(const Vec3<float>& c, const Vec3<float>& dr);
	
	/**
	 * Même fonction que la précédente mais ne nécessitant pas le calcul des sinus et cosinus si ils ont déjà été calculés.
	 */
	void rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz);
	
	/**
	 * Effectue un redimensionnement de centre c et de coefficients ds.
	 */
	void rescale(const Vec3<float>& c, const Vec3<float>& ds);
	
	/**
	 * Renvoie la position relative de a par rapport à b.
	 */
	friend Position operator- (const Position& a, const Position& b);
	
	/**
	 * Opérateur d'affichage d'une position.
	 * Print au format du fichier de description de niveau.
	 */
	friend std::ostream& operator<< (std::ostream& out, const Position& p);
};

#endif /* Instance_h */
