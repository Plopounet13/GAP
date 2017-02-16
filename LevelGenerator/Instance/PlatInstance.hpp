#ifndef PlatInstance_hpp
#define PlatInstance_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include "Vec3.hpp"
#include "Position.hpp"

class PlatInstance{
private:
	int ID;
	
	Position pos;
	std::vector<Vec3<float>> posSortie;
	std::vector<Position> pos4D;
	
public:
	//posSortie and pos4D parameters content are emptied;
	//Penser à donner position de sortie et 4D relative à la position d'origine de la plateforme
	PlatInstance(int id,
				 const Position& pos,
				 std::vector<Vec3<float>>& posSortie,
				 std::vector<Position>& pos4D);
	
	void translate(const Vec3<float>& d);
	void rotate(const Vec3<float>& dr);
	void rescale(const Vec3<float>& ds);
	void rotate(const Vec3<float>& c, const Vec3<float>& dr);
	void rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz);
	void rescale(const Vec3<float>& c, const Vec3<float>& ds);
	
	friend std::ostream& operator<< (std::ostream& out, const PlatInstance& p);
};


#endif
