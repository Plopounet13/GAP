#include <fstream>
#include "../LevelGenerator/levelGenerator.h"
#include "createWorld.h"
#define valid(p) (0 <= p.x() && p.x() < c_world_size && 0 <= p.y() && p.y() < c_world_size && 0 <= p.z() && p.z() < c_world_size)

const int32_t c_world_size = 200;

const int32_t c_height = 15, c_length_min = 40, c_length_max = 80, c_length_renderdistance = 200, c_phi_max = 90, c_theta_max = 90;
const int32_t nb_angles = 20;
double c_theta_0 = 90./nb_angles;

Library bibli;
Instance world;
int ID_first_plat = 1;
int ID_last_plat = 2;
int ID_checkpoint_plat = 3;
int ID_transition_plat = 18;

std::default_random_engine gen;

using namespace std;

// Renvoie X et Y tirés aléatoirements tels que la proba de la paire X,Y soit donnée par probas[X][Y]
bool choose(const vector<vector<int>>& probas, int& x, int& y){
	int total = 0;
	vector<int> totaux(probas.size());
	for (int i = 0; i < (int)probas.size(); ++i){
		for (int v : probas[i]){
			total += v;
		}
		totaux[i] = total;
	}
	if(total == 0){
        return false;
	}
	uniform_int_distribution<int> rd(0, total-1);
	int r =rd(gen);
	for (x = 0; x < (int)totaux.size()-1 && r >= totaux[x]; ++x);

	r -= (x ? totaux[x-1] : 0);

	for (y = 0; y < (int)probas[x].size() && r >= 0; ++y){
		r -= probas[x][y];
	}
	--y;
	return true;
}



void init_library(const string& listFileName, Library& lib){
	ofstream foo;
	foo.open("yop.txt");
	foo << "etyuo " << endl;
	ifstream fileList(listFileName);
	if (fileList.fail()){
		foo << "Impossible d'ouvrir la liste de fichiers de plateforme " + listFileName << endl;
		exit(144*12);
	}
	string fileName;
	while (fileList >> fileName){//getline(fileList, fileName)){
		foo << fileName << endl;
		ifstream platFile(fileName);

		if (platFile.fail()){
			cerr << "Impossible d'ouvrir le fichier de plateforme " + fileName << endl;
			exit(144*12);
		}

		Platform *p = new Platform(platFile);
		lib.push(p);

	}
}

uint32_t compute_proba(uint32_t length) {
	if(length < c_length_min) return 0;
	else return length-c_length_min;
}

uint32_t reverse_proba(uint32_t proba) {
	return proba+c_length_min;
}

void update_world(std::vector<std::vector<std::vector<bool> > >& world_bin, const Cuboid &cuboid)
{
 	Vecteur e_x, e_y, e_z;
	make_base(cuboid.dir, e_z, e_x, e_y);
	for(uint32_t k = -cuboid.height; k < cuboid.height; ++k) {
		for(uint32_t l = -cuboid.height; l < cuboid.height; ++l) {
            for(uint32_t m = 0; m < cuboid.length+c_height; ++m) {
                Point currPos =   cuboid.in + k*e_x + l*e_y + m*e_z;
                world_bin[currPos.x()][currPos.y()][currPos.z()]  = 1;
            }
		}
	}
}

Point randPoint(int maxy, int maxz){
	uniform_int_distribution<int> rdy(0, maxy);
	uniform_int_distribution<int> rdz(0, maxz);
	return Point(0, rdy(gen), rdz(gen));
}

bool next_cuboid(std::vector<std::vector<std::vector<bool> > >& world_bin, std::vector<Cuboid> &cuboids, Point& inPoint, bool lastSubLevel)
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
	for(int i = -nb_angles; i <= nb_angles; ++i) {
		for(int j = -nb_angles; j <= nb_angles; ++j) {
			Vecteur currVect =   i*e_x + j*e_y + nb_angles/5*e_z;
			Vecteur f_x, f_y, f_z;
			make_base(currVect, f_z, f_x, f_y);

			for(length = 0; length < c_length_renderdistance; ++length) {
                if(abs(i)<nb_angles/5 || abs(j)<nb_angles/5)
                    goto end_browse;
				for(uint32_t k = -c_height; k < c_height; ++k) {
					for(uint32_t l = -c_height; l < c_height; ++l) {

						Vecteur currPos = out + shift + k * e_x + l * e_y +  length*e_z ;
						if(valid(currPos) && world_bin[currPos.x()][currPos.y()][currPos.z()]) {
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
	if(!choose(probas, theta_1_choose, theta_2_choose))
        return false;
	length = reverse_proba(probas[theta_1_choose][theta_2_choose]);


	auto pair = std::make_pair(theta_1_choose-nb_angles, theta_2_choose-nb_angles);
	auto new_cuboid = Cuboid(out + shift, pair.first * e_x + pair.second * e_y + length * e_z, length);

	Instance new_instance;

	//TODO: Passer sur des points randoms ?
	Point newOut = Point(0, 5, 5);//randPoint(c_height, c_height);

	generationLocale(bibli, inPoint*100, (newOut+Point(new_cuboid.length, 0, 0))*100,
					 new_cuboid.length*100, new_cuboid.height*100, new_cuboid.height*100,
					 new_instance);

    ///* <begin> Plateforme de transition *///
    {
        Position posPremierePlat(0, inPoint*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
        vector<Vec3<float>> posSorties;
        vector<float> sortie4D;
        vector<Position> pos4D(1, posPremierePlat);

        PlatInstance premierePlat(ID_transition_plat, posPremierePlat, posSorties, sortie4D, pos4D, (float)rand());
        new_instance.addPlatform(premierePlat);
    }
    {
        int i=5;
        {
            Position posCpPlat(0, (newOut+Point((new_cuboid.length+i), 0, 0))*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
            vector<Position> posOut4D(1, posCpPlat);
            vector<Vec3<float>> posSorties;
            vector<float> sortie4D;
            PlatInstance plat_Cp(ID_checkpoint_plat, posCpPlat, posSorties, sortie4D, posOut4D, (float)rand());

            new_instance.addPlatform(plat_Cp);
        }
        for(i = 10; i<c_height; i+=5){
            Position posTransPlat(0, (newOut+Point((new_cuboid.length+i), 0, 0))*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
            vector<Position> posOut4D(1, posTransPlat);
            vector<Vec3<float>> posSorties;
            vector<float> sortie4D;
            PlatInstance plat_trans(ID_transition_plat, posTransPlat, posSorties, sortie4D, posOut4D, (float)rand());

            new_instance.addPlatform(plat_trans);
        }
    }

    ///* <end> Plateforme de transition *///

    update_world(world_bin, new_cuboid);

	new_instance.move(inPoint*100, new_cuboid.dir, (new_cuboid.in - inPoint)*100);
	world += new_instance;

	cuboids.push_back(new_cuboid);
	inPoint = newOut;
	return true;
}

void createWorld(ofstream& out) {

	std::vector<std::vector<std::vector<bool>>> world_bin(c_world_size, std::vector<std::vector<bool> > (c_world_size, std::vector<bool> (c_world_size, 0)));
	//TODO: Remplir des cases dans world_bin pour donner une forme au niveau
	std::vector<Cuboid> cuboids;

	uint32_t n = 2;

	//Create first cuboid
	cuboids.emplace_back(Point(0, 5, 5), Point(1, 0, 0), c_length_max);
	Point inPoint = Point(0, 0, -1);//randPoint(c_height, c_height);
	Point outPoint = Point(0, 5, 5);//randPoint(c_height, c_height);


	Position posPremierePlat(0, inPoint*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
	vector<Vec3<float>> posSorties;
	vector<float> sortie4D;
	vector<Position> pos4D(1, posPremierePlat);

	PlatInstance premierePlat(ID_first_plat, posPremierePlat, posSorties, sortie4D, pos4D, (float)rand());

	Instance sousNiveau;
	generationLocale(bibli, inPoint*100, (outPoint+ Point(c_length_max, 0, 0))*100, c_length_max*100, c_height*100, c_height*100, sousNiveau);
	sousNiveau.addPlatform(premierePlat);

    int i=5;
    {
        Position posCpPlat(0, (outPoint+Point((c_length_max+i), 0, 0))*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
        vector<Position> posOut4D(1, posCpPlat);
        vector<Vec3<float>> posSorties;
        vector<float> sortie4D;
        PlatInstance plat_Cp(ID_checkpoint_plat, posCpPlat, posSorties, sortie4D, posOut4D, (float)rand());

        sousNiveau.addPlatform(plat_Cp);
    }
    for(i = 10; i<c_height; i+=5){
        Position posTransPlat(0, (outPoint+Point((c_length_max+i), 0, 0))*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
        vector<Position> posOut4D(1, posTransPlat);
        vector<Vec3<float>> posSorties;
        vector<float> sortie4D;
        PlatInstance plat_trans(ID_transition_plat, posTransPlat, posSorties, sortie4D, posOut4D, (float)rand());

        sousNiveau.addPlatform(plat_trans);
    }
    /*for(int i = 0; i<c_height; i+=5){
        Position posTransPlat(0, (outPoint+Point((c_length_max+i), 0, 0))*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
        vector<Position> posOut4D(1, posTransPlat);
        vector<Vec3<float>> posSorties;
        vector<float> sortie4D;
        PlatInstance plat_trans(ID_transition_plat, posTransPlat, posSorties, sortie4D, posOut4D, rand());

        sousNiveau.addPlatform(plat_trans);
    }*/

	world+=sousNiveau;
    bool still_running = true;
	for(uint32_t i = 0; i < n && still_running; ++i) {
		still_running = next_cuboid(world_bin, cuboids, outPoint, (i==n-1));
	}
    {
        Instance new_instance;
        const Cuboid &last_cuboid  = cuboids.back();
        Position posDernierePlat(0, (outPoint+Point(last_cuboid.length+c_height, 0, 0))*100, Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
        vector<Position> posOut4D(1, posDernierePlat);
        vector<Vec3<float>> posSorties;
        vector<float> sortie4D;
        PlatInstance dernierePlat(ID_last_plat, posDernierePlat, posSorties, sortie4D, posOut4D, (float)rand());

        new_instance.addPlatform(dernierePlat);
        inPoint = Point(0, 5, 5); /// ATTENTION TEMPORAIRE
        new_instance.move(inPoint*100, last_cuboid.dir, (last_cuboid.in - inPoint)*100);
        world += new_instance;
    }

	out << world;
	out.close();
}
