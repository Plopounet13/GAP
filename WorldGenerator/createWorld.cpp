#include "createWorld.h"

using namespace std;

void init_library()
{
filebuf fb;
    if (fb.open ("patate.txt",ios::in))
    {
        istream is(&fb);
        
        Platform p = Platform(is) ;
        bibli.push(&p) ;
        
        fb.close();
    }
    else {
        cout << "mouais..." << endl ;
    }
}

uint32_t  compute_proba(uint32_t length) {
	if(length < c_length_min) return 0;
	else return length-c_length_min;
}

uint32_t  reverse_proba(uint32_t proba) {
	return proba+c_length_min;
}

void update_world(std::vector<std::vector<std::vector<int> > >& world_bin, const Cuboid &cuboid)
{
 	Vecteur e_x, e_y, e_z;
	base(cuboid.dir, e_z, e_x, e_y);
	for(uint32_t k = -c_height; k < c_height; ++k) {
		for(uint32_t l = -c_height; l < c_height; ++l) {
			Point currPos =   cuboid.in + k*e_x + l*e_y + nb_angles/2*e_x;
			world_bin[currPos.x()][currPos.y()][currPos.z()]  = 1;
		}
	}
}

void next_cuboid(std::vector<std::vector<std::vector<int> > >& world_bin, std::vector<Cuboid> &cuboids)
{
	std::map<std::pair<int, int>, double> probas;

	const Cuboid &last_cuboid  = cuboids.back();
	Vecteur v = last_cuboid.dir;
	Point out = last_cuboid.in + last_cuboid.length*last_cuboid.dir;

	Vecteur shift = c_height*last_cuboid.dir;
	uint32_t length;

	Vecteur e_x, e_y, e_z;
	make_base(v, e_z, e_x, e_y);
	for(int i = -nb_angles; i < nb_angles; ++i) { 
		for(int j = -nb_angles; j < nb_angles; ++j) {
			Vecteur currVect =   i*e_x + j*e_y + nb_angles/2*e_x;
			Vecteur f_x, f_y, f_z;
			make_base(currVect, f_z, f_x, f_y);

			
			for(length = 0; length < c_length_max; ++length) {
				for(uint32_t k = -c_height; k < c_height; ++k) {
					for(uint32_t l = -c_height; l < c_height; ++l) {
						Vecteur currPos = out + shift + k * e_y + l * e_x +  length*e_z ;
						if(world_bin[currPos.x()][currPos.y()][currPos.z()]  != 0) {
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

	
	auto pair = std::make_pair(1,1);
	auto new_cuboid = Cuboid(out + shift, pair.first * e_y + pair.second * e_x +  length*e_z, length);

	Instance new_instance;
	generationLocale(bibli, new_cuboid.in, new_cuboid.out, new_cuboid.length, new_cuboid.height, new_cuboid.height, new_instance);
	new_instance.move(in, dir); 
	world += new_instance;

	cuboids.push_back(new_cuboid);
}

void createWorld() {
	init_library();

	std::vector<std::vector<std::vector<int>>> world_bin(c_world_size, std::vector<std::vector<int> > (c_world_size, std::vector<int> (c_world_size, 0)));
	std::vector<Cuboid> cuboids;

	/// Create first cuboid
	cuboids.push_back(Cuboid(Point(0,0,0), Vecteur(1, 0, 0), c_length_max));

	uint32_t n = 10;
	for(uint32_t i = 0; i < n; ++i) {
		next_cuboid(world_bin, cuboids);
	}

	ofstream out("map.dat");
	out << instance <<  endl;
	out.close();
}
