#include "createWorld.h"

int compute_proba(size_t length) {
	if(length < c_length_min) return 0;
	else return length-c_length_min;
}

int reverse_proba() {

}

void update_world(std::vector<std::vector<std::vector<int> > >& world, const Cuboid &cuboid)
{

}

void next_cuboid(std::vector<std::vector<std::vector<int> > >& world, std::vector<Cuboid> &cuboid)
{
	std::map<std::pair<int, int>, double> probas;

	double theta = c_theta_0, phi = c_theta_0;
	for(size_t i = -nb_angles; i < nb_angles; ++i) { // i = theta
		for(size_t j = -nb_angles; j < nb_angles; ++j) { // j = phi
			vecteur e_x, e_y, e_z;
			size_t length;
			for(length = 0; length < c_length_max; ++length) {
				for(size_t k = -c_height; k < c_height; ++k) {
					for(size_t l = -c_height; l < c_height; ++l) {
						vecteur currPos = length*e_z + k * e_y + l * e_x;
						if(world[currPos.x()][currPos.y()][currPos.z()]  != 0) {
							goto end_browse;
						}
					}
				}
			}

			end_browse:
			probas[std::make_pair(i,j)] = compute_proba(length);
		}
	}

	cuboid = choose(probas);
}

void createWorld() {
	std::vector<std::vector<std::vector<int> > > world(c_world_size, std::vector<std::vector<int> > (c_world_size, std::vector<int> (c_world_size, 0)));
	std::vector<Cuboid> cuboids;

	/// Create first cuboid
	cuboids.push_back(Cuboid(c_length_max, c_height, 0, 0, 0, Point(0,0,0)));

	size_t n = 10;
	for(size_t i = 0; i < n; ++i) {
		next_cuboid(world, cuboids);
	}
}
