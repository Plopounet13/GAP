#include <iostream>
#include <fstream>
#include "Library.h"
#include "Platform.h"


using namespace std;


//Permet de récupérer les platforme ayant une accélération additive en 4eme dimension non nulle
bool filtre1(const Platform& p){
	const Point& point = p.getAddAcceleration();
	return (point.getK()!=0);
}

bool specialFilter(const Platform& p, int minWantedAngle){
	for(int v:p.getAngleSorties()){
		if (v>=minWantedAngle)
			return true;
	}
	return false;
}

int main(int argc, const char * argv[]) {
	
	Library lib;
	
	ifstream in("./input.txt");
	if (in.fail()){
		cerr << "Fail to open file ./input.txt" << endl;
		return 1;
	}
	
	cout << "Creating New platform with ID ";
	Platform* p = new Platform(in);
	
	cout << p->getID() << endl;
	
	ifstream in2("./input2.txt");
	if (in2.fail()){
		cerr << "Fail to open file ./input2.txt" << endl;
		return 1;
	}
	
	cout << "Creating New platform with ID ";
	Platform* p2 = new Platform(in2);
	
	cout << p2->getID() << endl;
	
	lib.push(p);
	lib.push(p2);
	
	vector<Platform *> platSet;
	//Récupère dans platSet les plateformes avec une acceleration selon K
	lib.select(filtre1, platSet);
	
	cout << "Platform with acceleration along K:"<<endl;
	for (Platform* plat:platSet){
		cout << plat->getID() << endl;
	}
	
	//Récupère dans platSet les plateformes avec un angle >= 1
	lib.select(bind(specialFilter, placeholders::_1, 1), platSet);
	//read bind documentation on C++reference or ask me if any question
	
	cout << "Platform with angle >= 1:"<<endl;
	for (Platform* plat:platSet){
		cout << plat->getID() << endl;
	}
	
    return 0;
}
