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


// fonctions pour select



bool f_monte(const Platform& p)
{
    for(int v:p.getAngleSorties()){
		if (v>=1)
			return true;
	}
	return false;
}

bool f_descend(const Platform& p)
{
    for(int v:p.getAngleSorties()){
		if (v<=-1)
			return true;
	}
	return false;
}

bool f_plat(const Platform& p)
{
    for(int v:p.getAngleSorties()){
		if (v==0)
			return true;
	}
	return false;
}

bool f_true(const Platform& p)
{
    return true;
}
