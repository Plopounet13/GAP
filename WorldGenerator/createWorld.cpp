#include <fstream>
#include "../LevelGenerator/levelGenerator.h"
#include "createWorld.h"


const uint32_t c_world_size = 400;

const uint32_t c_height = 10, c_length_min = 40, c_length_max = 80, c_phi_max = 90, c_theta_max = 90;
const uint32_t nb_angles = 20;
double c_theta_0 = 90./nb_angles;

Library bibli;
Instance world;
int ID_first_plat = 1;
int ID_last_plat = 2;

std::default_random_engine gen;

using namespace std;

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

Point randPoint(int maxy, int maxz){
	uniform_int_distribution<int> rdy(0, maxy);
	uniform_int_distribution<int> rdz(0, maxz);
	return Point(0, rdy(gen), rdz(gen));
}

void next_cuboid(std::vector<std::vector<std::vector<int> > >& world_bin, std::vector<Cuboid> &cuboids, Point& inPoint, bool lastSubLevel)
{
	std::vector<std::vector<int>> probas(2*nb_angles + 1, vector<int>(2*nb_angles + 1));

	const Cuboid &last_cuboid  = cuboids.back();
	Vecteur v = last_cuboid.dir;
	Point out = last_cuboid.in + last_cuboid.length*last_cuboid.dir;

	//On décale le nouveau sous niveau de c_height dans la direction du précédent (on le décale dans l'alignement)
	Vecteur shift = c_height*last_cuboid.dir;
	uint32_t length=0;

	Vecteur e_x, e_y, e_z;
	make_base(v, e_z, e_x, e_y);
	//TODO: Pourquoi pas <= ?
	for(int i = -nb_angles; i <= nb_angles; ++i) {
		for(int j = -nb_angles; j <= nb_angles; ++j) {
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
			probas[i + nb_angles][j + nb_angles] = compute_proba(length);
		}
	}

	
	int theta_1_choose, theta_2_choose;
	choose(probas, theta_1_choose, theta_2_choose);
	length = reverse_proba(probas[theta_1_choose][theta_2_choose]);

	
	auto pair = std::make_pair(theta_1_choose, theta_2_choose);
	auto new_cuboid = Cuboid(out + shift, pair.first * e_y + pair.second * e_x +  length * e_z, length);

	//TODO: Parler avec Thomas de cette partie (bien positionner les point de début et fin)
	Instance new_instance;
	
	Point newOut = randPoint(new_cuboid.height*10, new_cuboid.height*10);
	
	generationLocale(bibli, inPoint, newOut+Point(new_cuboid.length*10, 0, 0),
					 new_cuboid.length*10, new_cuboid.height*10, new_cuboid.height*10,
					 new_instance);
	
	//Si in = new_cuboid.in plein de problemes (move need coin inf et generation locale need être placé à 0/0/0 pas directement là où tu en as besoin
	
	//TODO: où sont les plateformes de transition ? (Il faut rajouter celles entre last_cuboid et new_cuboid)
	
	
	if (lastSubLevel){
		Position posDernierePlat(0, newOut+Point(new_cuboid.length*10, 0, 0), Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
		vector<Position> posOut4D(1, posDernierePlat);
		vector<Vec3<float>> posSorties;
		vector<float> sortie4D;
		PlatInstance dernierePlat(ID_last_plat, posDernierePlat, posSorties, sortie4D, posOut4D, (float)rand()/(float)RAND_MAX);
		
		new_instance.addPlatform(dernierePlat);
	}
	
	new_instance.move(new_cuboid.in, new_cuboid.dir);
	
	world += new_instance;

	cuboids.push_back(new_cuboid);
	inPoint = newOut;
}

void createWorld(ofstream& out) {

	std::vector<std::vector<std::vector<int>>> world_bin(c_world_size, std::vector<std::vector<int> > (c_world_size, std::vector<int> (c_world_size, 0)));
	std::vector<Cuboid> cuboids;

	uint32_t n = 10;
	
	//Create first cuboid
	cuboids.emplace_back(Point(0, 5, 5), Point(1, 0, 0), c_length_max*10);
	Point inPoint = randPoint(c_height*10, c_height*10);
	Point outPoint = randPoint(c_height*10, c_height*10);
	
	//TODO: Place initial platform at inPoint
	Position posPremierePlat(0, Vec3<float>(0, 5, 5), Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
	vector<Vec3<float>> posSorties;
	vector<float> sortie4D;
	vector<Position> pos4D(1, posPremierePlat);
	
	PlatInstance premierePlat(ID_first_plat, posPremierePlat, posSorties, sortie4D, pos4D, (float)rand()/(float)RAND_MAX);
	
	Instance sousNiveau;
	generationLocale(bibli, inPoint, outPoint + Point(c_length_max*10, 0, 0), c_length_max*10, c_height*10, c_height*10, sousNiveau);
	sousNiveau.addPlatform(premierePlat);
	world+=sousNiveau;
	Point posFin;
	
	for(uint32_t i = 0; i < n; ++i) {
		next_cuboid(world_bin, cuboids, outPoint, (i==n-1));
	}
	

	out << world;
	out.close();
}
