#include <sstream>
#include <algorithm>
#include <map>
#include "Platform.h"

using namespace std;

Platform::Platform():ID(0){}

Platform::Platform(int ID,
				   vector<Forme>& formes,
				   Point& additiveAcceleration,
				   Point& multiplicativeAcceleration,
				   std::vector<Point>& distSorties,
				   std::vector<int>& angleSorties,
				   bool reshapeAble,
				   Point& size,
				   int apparitionWeight):ID(ID),
									 formes(formes),
									 distSorties(distSorties),
									 angleSorties(angleSorties),
									 reshapeAble(reshapeAble),
									 additiveAcceleration(additiveAcceleration),
									 multiplicativeAcceleration(multiplicativeAcceleration),
									 size(size),
									 apparitionWeight(apparitionWeight){}

void split(const string s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

void removeChars(string &str, string charsToRemove ) {
	for (char c:charsToRemove) {
		str.erase(remove(str.begin(), str.end(), c), str.end() );
	}
}

Platform::Platform(istream& in){
	string line;
	map<string, bool> vu;
	apparitionWeight=DEFAULT_WEIGHT;
	while(getline(in, line)){
		//Uncomment to print parsed input file
		//cout << line << endl;
		vector<string> val;
		split(line, '=', val);
		removeChars(val[0], " \t");
		if (vu[val[0]]){
			cerr << "Erreur fichier description plateforme: " << val[0] << " défini plusieurs fois." << endl;
		}else{
			vu[val[0]]=true;
			if (val[0]=="ID"){
				ID=atoi(val[1].c_str());
				
			}else if (val[0]=="formes"){
				stringstream ss;
				ss.str(val[1]);
				int v;
				while (ss >> v)
					formes.push_back((Forme)v);
					
			}else if (val[0]=="additiveAcceleration"){
				stringstream ss;
				ss.str(val[1]);
				int v1, v2, v3, v4;
				ss >> v1 >> v2 >> v3 >> v4;
				additiveAcceleration = Point(v1, v2, v3, v4);
				
			}else if (val[0]=="multiplicativeAcceleration"){
				stringstream ss;
				ss.str(val[1]);
				int v1, v2, v3, v4;
				ss >> v1 >> v2 >> v3 >> v4;
				multiplicativeAcceleration = Point(v1, v2, v3, v4);
				
			}else if (val[0]=="distSorties"){
				stringstream ss;
				ss.str(val[1]);
				int x, y, z, q;
				char t;
				while (ss >> t >> x >> y >> z >> q >> t){
					distSorties.emplace_back(x, y, z, q);
				}
				
			}else if (val[0]=="angleSorties"){
				stringstream ss;
				ss.str(val[1]);
				int a;
				while (ss >> a){
					angleSorties.push_back(a);
				}
				
			}else if (val[0]=="reshapeAble"){
				stringstream ss;
				ss.str(val[1]);
				string val;
				ss >> val;
				reshapeAble=(val == "true");
				
			}else if (val[0]=="size"){
				stringstream ss;
				ss.str(val[1]);
				int v1, v2, v3;
				ss >> v1 >> v2 >> v3;
				size=Point(v1,v2,v3);
				
			}else if (val[0]=="apparitionWeight"){
				stringstream ss;
				ss.str(val[1]);
				int v;
				ss >> v;
				apparitionWeight=v;
				
			}else{
				cerr << "Erreur fichier description plateforme: " << val[0] << " n'est pas un attribut valide." << endl;
			}
		}
	}
	
}

int Platform::getID() const {
	return ID ;
}

int Platform::getNbFormes() const{
	return formes.size();
}

const vector<Forme>& Platform::getFormes() const{
	return formes;
}

const Point& Platform::getAddAcceleration() const{
	return additiveAcceleration;
}

const Point& Platform::getCoeffAcceleration() const{
	return multiplicativeAcceleration;
}

int Platform::getNbSorties() const{
	return distSorties.size();
}

const vector<Point>& Platform::getDistSorties() const{
	return distSorties;
}

const vector<int>& Platform::getAngleSorties() const{
	return angleSorties;
}
bool Platform::getReshapeAble() const{
	return reshapeAble;
}

Platform::~Platform() {
}
