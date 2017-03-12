#include <map>
#include <vector>
#include "functions.h"
#define Point point
#define Vecteur vecteur

const size_t c_world_size = 400;

const size_t c_height = 10, c_length_min = 40, c_length_max = 80, c_phi_max = 90, c_theta_max = 90;
const size_t nb_angles = 20;
double c_theta_0 = 90./nb_angles;

class Cuboid
{
public:
	Cuboid(double l, double h, double th, double ph, double ps, Point i) : length(l), height(h), theta(th), phi(ph), psi(ps), in(i) {

	}

//private:
	point in, out;
	double theta, phi, psi;
	double length, height;
};

void createWorld();
