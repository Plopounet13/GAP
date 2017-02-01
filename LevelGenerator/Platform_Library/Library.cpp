#include "Library.h"

using namespace std;

Library::Library(){}

void Library::push(Platform* p){
	platList.push_back(p);
}

void Library::select(function<bool (const Platform&)> f, vector<Platform *>& res) const{
	res.clear();
	for (Platform* p:platList){
		if (f(*p)){
			res.push_back(p);
		}
	}
}
