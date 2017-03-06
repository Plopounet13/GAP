#include <sstream>
#include <algorithm>
#include <map>
#include "Platform.h"

using namespace std;

Platform::Platform():ID(0){}

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

void Platform::parse(istream& in){
	string line;
	map<string, bool> vu;
	apparitionWeight=DEFAULT_WEIGHT;
	isTransition=false;
	modifiable=false;
	additiveAcceleration = Point(0,0,0,0);
	multiplicativeAcceleration = Point(1,1,1,1);
	nbSorties=0;

	while(getline(in, line)){
		//Uncomment to print parsed input file
		//cout << line << endl;
		vector<string> val;
		split(line, '=', val);
		removeChars(val[0], " \t");
		if (val[0][0]=='%'){
			continue;
		}
		if (vu[val[0]]){
			cerr << "Erreur fichier description plateforme: " << val[0] << " défini plusieurs fois." << endl;
		}else{
			vu[val[0]]=true;
			if (val[0]=="ID"){
				ID=atoi(val[1].c_str());
				
			}else if (val[0]=="nbSortie"){
				stringstream ss;
				ss.str(val[1]);
				ss >> nbSorties;
				
			}else if (val[0]=="paveSortie"){
				stringstream ss;
				ss.str(val[1]);
				
				int x, y, z, q;
				char t;
				
				while (ss >> t >> x >> y >> z >> q >> t){
					sortieMin.emplace_back(x,y,z,q);
					ss >> t >> x >> y >> z >> q >> t;
					sortieMax.emplace_back(x,y,z,q);
				}
				
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
				
			}else if (val[0]=="scales"){
				stringstream ss;
				ss.str(val[1]);
				
				char t;
				
				ss >> t >> minScale >> t;
				ss >> t >> maxScale >> t;
				
			}else if (val[0]=="rotations"){
				stringstream ss;
				ss.str(val[1]);
				
				char t;
				
				ss >> t >> minRot >> t;
				ss >> t >> maxRot >> t;
				
			}else if (val[0]=="isTransition"){
				stringstream ss;
				ss.str(val[1]);
				
				string s;
				
				ss >> s;
				isTransition = (s=="true");
				
			}else if (val[0]=="4Dmodifiable"){
				stringstream ss;
				ss.str(val[1]);
				
				string s;
				
				ss >> s;
				modifiable = (s=="true");
				
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

Platform::Platform(istream& in){
	parse(in);
}

std::istream& operator>> (istream& in, Platform& p){
	p.parse(in);
	return in;
}

int Platform::getID() const {
	return ID ;
}

const Point& Platform::getAddAcceleration() const{
	return additiveAcceleration;
}

const Point& Platform::getCoeffAcceleration() const{
	return multiplicativeAcceleration;
}

int Platform::getNbSorties() const{
	return nbSorties;
}

const vector<Point>& Platform::getSortieMin() const{
	return sortieMin;
}

const vector<Point>& Platform::getSortieMax() const{
	return sortieMax;
}

const Vec3<float>& Platform::getMinScale() const{
	return minScale;
}

const Vec3<float>& Platform::getMaxScale() const{
	return maxScale;
}

bool Platform::getModifiable() const{
	return modifiable;
}

Platform::~Platform() {
}
