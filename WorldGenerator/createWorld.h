#include <map>
#include <vector>
#include "functions.h"

const uint32_t c_world_size = 400;

const uint32_t c_height = 10, c_length_min = 40, c_length_max = 80, c_phi_max = 90, c_theta_max = 90;
const uint32_t nb_angles = 20;
double c_theta_0 = 90./nb_angles;

class Cuboid
{
public:
	Cuboid(Point i, Vecteur d, double l, double h = c_height) : length(l), height(h), in(i), dir(d) {
		d.mult(1./d.length());
	}

//private:
	const Point in;
	//double theta, phi, psi;
	const Vecteur dir;
	const double length, height;
};

void createWorld();
