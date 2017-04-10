#ifdef _WIN32
	#include <windows.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cmath>
#include "createWorld.h"

#define XCODE_DEBUG 0

using namespace std;

void usage(){
	cerr << "usage:" << endl;
	cerr << "\t./generate_level outputFile seed" << endl;
}

/*int main(){
	Position posPremierePlat(0, Vec3<float>(0, 0, 5), Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
	vector<Vec3<float>> posSorties;
	vector<float> sortie4D;
	vector<Position> pos4D(1, posPremierePlat);

	PlatInstance premierePlat(0, posPremierePlat, posSorties, sortie4D, pos4D, (float)rand());


	Position posPremierePlat2(0, Vec3<float>(0, 0, 0), Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1));
	vector<Vec3<float>> posSorties2;
	vector<float> sortie4D2;
	vector<Position> pos4D2(1, posPremierePlat2);

	PlatInstance premierePlat2(0, posPremierePlat2, posSorties2, sortie4D2, pos4D2, (float)rand());

	Vec3<float> v(1,1,1), v2(1,1,1);
	v.rotate(Vec3<float>(0, 0, 90));
	v2.rotate(Vec3<float>(0, 0, 45));


	Instance i;
	i.addPlatform(premierePlat);
	i.addPlatform(premierePlat2);

	i.move(Vec3<float>(0, 1, 1), Vec3<float>(0, 0, 0));

	cout << i << endl;
}*/


int main(int argc, const char* argv[]) {


	ofstream out;
	int seed;
	string listFileName = "..\\/..\\/platform_file_list.txt";

#if XCODE_DEBUG != 0
	out.open("level.dat");
	seed = 42;
	listFileName = "/Users/lois/Documents/M1ENS/GAPLocalProject/GAPLocalProject/GAP/my_platform_file_list.txt";
	goto skipInit;
#endif

	if (argc != 3){
		cerr << "Error: Wrong number of parameters " << endl << endl;
		usage();
		exit (1);
	}

	out.open("..\\/..\\/Levels\\/" + (string)argv[1]+".user.dat");
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

	init_library(listFileName, bibli);
	out << seed << endl;
	createWorld(out);
	out.close();
	return 0;
}











