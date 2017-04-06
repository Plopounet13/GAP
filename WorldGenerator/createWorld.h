#include <map>
#include <vector>
#include <random>
//#include "../LevelGenerator/Library/Point.h"
#include "../LevelGenerator/Library/Platform.h"
#include "../LevelGenerator/Library/Library.h"
#include "../LevelGenerator/Instance/Instance.h"
#include "../LevelGenerator/Instance/PlatInstance.h"
#include "../LevelGenerator/Instance/Position.h"
#include "../LevelGenerator/Instance/Vec3.h"
#include "../LevelGenerator/Polynome.h"
#include "functions.h"


extern const int32_t c_world_size;

extern const int32_t c_height, c_length_min, c_length_max, c_phi_max, c_theta_max;
extern const int32_t nb_angles;
extern double c_theta_0;

extern Library bibli;
extern Instance world;

extern std::default_random_engine gen;

void init_library(const std::string& listFileName, Library& lib);

class Cuboid
{
public:
	Cuboid(Point i, Vecteur d, double l, double h = c_height) : length(l), height(h), in(i), dir(d) {
		dir.mult(1./dir.length());
		out = in + dir*l;
	}

//private:
	double length, height;
	Point in, out;
	//double theta, phi, psi;
	Vecteur dir;
};

void createWorld(std::ofstream& out);

/*
move(Point in, Vector dir); takes the  entry point of the cuboid and the director vector and moves the cuboid from (0,0,0), (1,0,0) to point, dir
*/
