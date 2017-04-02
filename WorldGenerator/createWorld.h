#include <map>
#include <vector>
//#include "../LevelGenerator/Library/Point.h"
#include "../LevelGenerator/Library/Platform.h"
#include "../LevelGenerator/Library/Library.h"
#include "../LevelGenerator/Instance/Instance.h"
#include "../LevelGenerator/Instance/PlatInstance.h"
#include "../LevelGenerator/Instance/Position.h"
#include "../LevelGenerator/Instance/Vec3.h"
#include "../LevelGenerator/Polynome.h"
#include "functions.h"

//TODO: NOOOOOON !!!! pas de variable globale dans un .h
extern const uint32_t c_world_size;

extern const uint32_t c_height, c_length_min, c_length_max, c_phi_max, c_theta_max;
extern const uint32_t nb_angles;
extern double c_theta_0;

extern Library bibli;
extern Instance world;

void init_library(const std::string& listFileName, Library& lib);

class Cuboid
{
public:
	Cuboid(Point i, Vecteur d, double l, double h = c_height) : length(l), height(h), in(i), dir(d) {
		d.mult(1./d.length());
		out = in + dir*l;
	}

//private:
	Point in, out;
	//double theta, phi, psi;
	Vecteur dir;
	double length, height;
};

void createWorld();

/*
move(Point in, Vector dir); takes the  entry point of the cuboid and the director vector and moves the cuboid from (0,0,0), (1,0,0) to point, dir
*/
