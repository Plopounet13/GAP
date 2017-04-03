#include <fstream>
#include "../LevelGenerator/levelGenerator.h"
#include "createWorld.h"
#include <random>


const uint32_t c_world_size = 400;

const uint32_t c_height = 10, c_length_min = 40, c_length_max = 80, c_phi_max = 90, c_theta_max = 90;
const uint32_t nb_angles = 20;
double c_theta_0 = 90./nb_angles;

Library bibli;
Instance world;

using namespace std;


int seed=42;
default_random_engine gen(seed);
// Renvoie X et Y tirés aléatoirements tels que la proba de la paire X,Y soit donnée par probas[X][Y]
void choose(const vector<vector<int>>& probas, int& x, int& y){
	int total = 0;
	vector<int> totaux(probas.size());
	for (int i = 0; i < probas.size(); ++i){
		for (int v : probas[i]){
			total += v;
		}
		totaux[i] = total;
	}
	uniform_int_distribution<int> rd(0, total-1);
	int r =rd(gen);
	for (x = 0; x < totaux.size()-1 && r >= totaux[x]; ++x);
	
	r -= (x ? totaux[x-1] : 0);
	
	for (y = 0; y < probas[x].size() && r >= 0; ++y){
		r -= probas[x][y];
	}
	--y;
}



void init_library(const string& listFileName, Library& lib){
	ifstream fileList(listFileName);
	if (fileList.fail()){
		cerr << "Impossible d'ouvrir la liste de fichiers de plateforme " + listFileName << endl;
		exit(144*12);
	}
	string fileName;
	while (getline(fileList, fileName)){
		
		ifstream platFile(fileName);
		
		if (platFile.fail()){
			cerr << "Impossible d'ouvrir le fichier de plateforme " + fileName << endl;
			exit(144*12);
		}
		
		Platform *p = new Platform(platFile);
		lib.push(p);
		
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
	make_base(cuboid.dir, e_z, e_x, e_y);
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
	uint32_t length=0;

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

	//TODO: Va falloir discuter de vos typage les gars...
	int theta_1_choose, theta_2_choose;
	//choose(probas, theta_1_choose, theta_2_choose);
	//length = reverse_proba(probas[theta_1_choose][theta_2_choose]));
	length = 80;

	//TODO: La taille du sous niveau ne va pas le faire
	auto pair = std::make_pair(1,1);
	auto new_cuboid = Cuboid(out + shift, pair.first * e_y + pair.second * e_x +  length*e_z, length);

	//TODO: Parler avec Thomas de cette partie
	Instance new_instance;
	generationLocale(bibli, new_cuboid.in, new_cuboid.out, new_cuboid.length, new_cuboid.height, new_cuboid.height, new_instance);
	//Si in = new_cuboid.in plein de problemes (move need coin inf et generation locale need être placé à 0/0/0 pas directement là où tu en as besoin
	//new_instance.move(in, dir);
	world += new_instance;
	
	//TODO: où sont les plateformes de transition ?

	cuboids.push_back(new_cuboid);
}

void createWorld() {
	init_library("/Users/lois/Documents/M1ENS/GAPLocalProject/GAPLocalProject/GAP/platform_file_list.txt", bibli);

	std::vector<std::vector<std::vector<int>>> world_bin(c_world_size, std::vector<std::vector<int> > (c_world_size, std::vector<int> (c_world_size, 0)));
	std::vector<Cuboid> cuboids;

	/// Create first cuboid
	cuboids.push_back(Cuboid(Point(0,0,0), Vecteur(1, 0, 0), c_length_max));

	uint32_t n = 10;
	for(uint32_t i = 0; i < n; ++i) {
		next_cuboid(world_bin, cuboids);
	}

	ofstream out("map.dat");
	out << world;
	out.close();
}
