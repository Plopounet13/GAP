#include <iostream>
#include <fstream>
#include <vector>
#include <math.h> 
#include "createWorld.h"

#define XCODE_DEBUG 0

using namespace std;

void usage(){
	cerr << "usage:" << endl;
	cerr << "\t./generate_level outputFile seed" << endl;
}

int main(int argc, const char* argv[]) {
	ofstream out;
	int seed;
	
#if XCODE_DEBUG != 0
	out.open("level.dat");
	seed = 42;
	goto skipInit;
#endif
	
	if (argc != 3){
		cerr << "Error: Wrong number of parameters" << endl << endl;
		usage();
		exit (1);
	}
	
	out.open(argv[1]);
	if (out.fail()){
		cerr << "Error: Impossible to create output file" << endl << endl;
		usage();
		exit(2);
	}
	
	seed = atoi(argv[2]);

skipInit:
	
	//TODO: Generate pseudo random serie to have install independent random
	srand(seed);
	gen.seed(seed);
	
	init_library("/Users/lois/Documents/M1ENS/GAPLocalProject/GAPLocalProject/GAP/platform_file_list.txt", bibli);
	
	createWorld(out);
}

/*
// Width needs to be odd, nbDirections needs to be even
const int slvlLengthMin = 40, slvlLengthMax = 80, slvlWidth = 11, lvlSize = 200;
const short nbDirections = 4;
short world[lvlSize][lvlSize][lvlSize];

// Implement vectors and points
struct Point
{
	double x, y, z;
};

std::ostream& operator<< (std::ostream &o, const Point &p)
{
  o << "x: " << p.x << "\ty: " << p.y << "\tz: " << p.z << endl;
  return o;
}



double randomReal(double max = 1)
{
	return (static_cast<float> (rand()) / static_cast<float> (RAND_MAX)) * max;
}

int randomInt(int a, int b) {
	return (rand() % (b-a+1)) + a;
}

int discreteProba(vector<double> proba, double max = 1)
{
	double x = randomReal(max);

	double p = 0;
	for(size_t i = 0; i < proba.size(); ++i) {
		p += proba[i];
		if(x <= p)
			return i;
	}
}


Point pointFromSpheric(Point p, double tilt, double length, double orientation)
{
	double rho = length, theta = orientation, phi = M_PI/2-tilt;
	cout << endl << rho << " " << theta << " " << phi << endl;
	return {p.x + rho * sin(phi) * cos(theta), p.y + rho * sin(phi) * sin(theta), p.z + rho * cos(phi)};
}

void printToPython(vector<Point> points)
{
	string str;
	ostringstream oss;

	oss << "[";
	for(auto &p: points)
		oss << p.x << ", ";
	oss << "],";
	oss << "[";
	for(auto &p: points)
		oss << p.y << ", ";
	oss << "],";
	oss << "[";
	for(auto &p: points)
		oss << p.z << ", ";
	oss << "]" << endl;

	str = oss.str();

	system((string("echo '") + str + "' | python plot.py").c_str());
}

bool inLevel(size_t x, size_t y, size_t z) {
	return (x < lvlSize) && (x >= 0) && (y < lvlSize) && (y >= 0) && (z < lvlSize) && (z >= 0);
}

bool isFree(size_t x, size_t y, size_t z) {
	return inLevel(x, y, z) && level[x][y][z] == 0;
}

bool generateSubLevel(const Point &p)
{
	float probaDirections[nbDirections][nbDirection/2];
	int sumCoefs;

	for(size_t i = 0; i < nbDirections; ++i) {
		for(size_t j = 0; j < nbDirections/2; ++j) {
			short dx = 0, dy = 0, dz = 0;
			if(j == 0) { // Horizontal movement
				if(i%2 == 0)
					dx = -1;
				else
					dy = -1;
			}
			else { // Vertical movement
				if(i%2 == 0)
					dz = -1;
				else
					dy = -1;
			}

			if(i < 2) {
				dx *= dx;
				dy *= dy;
				dz *= dz;
			}

			// We browse the direction
			bool bExit = false;
			for(size_t k = 0; k < slvlLengthMax && !bExit; ++k) {
				for(size_t l = -slvlWidth/2; l < slvlWidth/2 && !bExit; ++l) {
					for(size_t m = -slvlWidth/2; m < slvlWidth/2 && !bExit; ++m) {
						int x = p.x + k*dx + l*abs(dy) + m*abs(dz),
							y = p.y * k*dy + l*abs(dx) + m*abs(dz),
							z = p.z + k*dz + l*abs(dx) + m*abs(dy);


						if(!isFree(x, y, z)) {
							if(k < slvlLengthMin)
								probaDirections[i][j] = 0;
							else
								probaDirections[i][j] = i;
							sumCoefs += probaDirections[i][j];
							bExit = true;
						}
				}
			}
		}
	}

	if(sumCoefs == 0) 
		return false;

	int 

	return true;
}



int main()
{
	srand(time(NULL));

	Point startPoint = {lvlSize/2, lvlSize/2, lvlSize/2};

	vector<Point> points =  {start_point};
	vector<Cuboid> level = {};

	cout << start_point << endl;
	for(size_t i = 0; i < 10; ++i) {
		createSubLevel();
		int tf = discrete_proba(proba_orientation);
		double tilt = random_tilt(tf);

		double length = 8 + 4*random_real();
		double orientation = 360*random_real()/180*M_PI;
		//cout << tf;

		Point new_point = pointFromSpheric(points.back(), tf, length, orientation);
		points.push_back(new_point);
		//cout << new_point;
	}

	printToPython(points);

	return 0;
}startPoint

*/
