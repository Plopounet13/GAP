#ifndef PlatInstance_hpp
#define PlatInstance_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include "Vec3.hpp"
#include "Position.hpp"

//TODO: Placer les sorties en 4 dimension au lieu de 3.

class PlatInstance{
private:
	int ID;
	
	Position pos;
	std::vector<Vec3<float>> posSortie;
	std::vector<Position> pos4D;
	int rand;
	
public:
	/**
	 *
	 * Le contenu de posSortie et pos4D est vidé
	 * Les coordonnées des sorties et des positions 4D sont à donner en absolu même si elle sont affichées en relatif dans le fichier final.
	*/
	PlatInstance(int id,
				 const Position& pos,
				 std::vector<Vec3<float>>& posSortie,
				 std::vector<Position>& pos4D,
				 int rand);
	
	/**
	 * deplace la plateforme d'un vecteur d dans l'espace.
	 */
	void translate(const Vec3<float>& d);
	
	/**
	 * Effectue une rotation centrale de la plateforme selon les angles dans dr.
	 */
	void rotate(const Vec3<float>& dr);
	
	/**
	 * Redimensionne la plateforme selon les coefficients dans ds.
	 */
	void rescale(const Vec3<float>& ds);
	
	/**
	 * Effectue une rotation de centre c et d'angles dr sur la plateforme.
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
	 * Opérateur d'affichage d'une instance de plateforme.
	 * Print au format du fichier de description de niveau.
	 */
	friend std::ostream& operator<< (std::ostream& out, const PlatInstance& p);
};


#endif
