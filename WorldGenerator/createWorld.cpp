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

void next_cuboid(std::vector<std::vector<std::vector<int> > >& world, std::vector<Cuboid> &cuboids)
{
	std::map<std::pair<int, int>, double> probas;

	const Cuboid &last_cuboid  = cuboids.back();
	Vecteur v = last_cuboid.dir;
	Point out = last_cuboid.in + last_cuboid.dir*last_cuboid.length;

	Vecteur e_x, e_y, e_z;
	base(v, e_z, e_x, e_y);
	for(int i = -nb_angles; i < nb_angles; ++i) { 
		for(int j = -nb_angles; j < nb_angles ++j) {
			Vecteur currVect =   i*e_x + j*e_y + nb_angles/2*e_x;
			Vecteur f_x, f_y, f_z;
			base(currVect, f_z, f_x,, f_y); 

			Vecteur shift = cuboids.back().dir*c_height;

			for(size_t length = 0; length < c_length_max; ++length) {
				for(size_t k = -c_height; k < c_height; ++k) {
					for(size_t l = -c_height; l < c_height; ++l) {
						Vecteur currPos = out + shift + k * e_y + l * e_x +  length*e_z ;
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

	//cuboid = choose(probas);
	pair = std::make_pair(1,1);

}

void createWorld() {
	std::vector<std::vector<std::vector<int> > > world(c_world_size, std::vector<std::vector<int> > (c_world_size, std::vector<int> (c_world_size, 0)));
	std::vector<Cuboid> cuboids;

	/// Create first cuboid
	cuboids.push_back(Cuboid(c_length_max, c_height, Point(0,0,0), Vecteur(1, 0, 0)));

	size_t n = 10;
	for(size_t i = 0; i < n; ++i) {
		next_cuboid(world, cuboids);
	}
}
