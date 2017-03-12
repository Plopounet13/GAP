#include "createWorld.h"

int compute_proba(double length) {
	if(length < c_length_min) return 0;
	else return length-c_length_min;
}

int reverse_proba() {

}

void update_world(int ***world, const Cuboid &cuboid)
{

}

void next_cuboid(int ***world, vector<Cuboid> &world);
{
	std::map<std::pair<int, int>, double> probas;

	double theta = c_theta_0, phi = c_theta_0; 
	for(int i = -nb_angles; i < nb_angles) { // i = theta
		for(int j = -nb_angles; j < nb_angles) { // j = phi
			type e_x, e_y, e_z;
			for(size_t length = 0; length < c_length_max; ++length) {
				for(int k = -height; k < height; ++k) {
					for(int l = -height; l < height; ++l) {
						int currPos = length*e_z + k * e_y + l * e_x;
						if(world[currPos.x][currPos.y][currPos.z]  != 0) {
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
	int world[c_world_size][c_world_size][c_world_size] = {};
	std::vector<Cuboid> cuboids;

	/// Create first cuboid
	world.push_back(Cuboid(c_max_length, c_height, 0, 0, Point(0,0,0)));

	size_t n = 10;
	for(size_t i = 0; i < n; ++i) {
		next_cuboid(world, cuboids);
	}
}