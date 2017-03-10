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


// fonctions pour select, a recoder



bool f_monte(const Platform& p)
{
	/*
    for(int v:p.getAngleSorties()){
		if (v>=1)
			return true;
	}
	*/
	return false;
}

bool f_descend(const Platform& p)
{
	/*
    for(int v:p.getAngleSorties()){
		if (v<=-1)
			return true;
	}
	*/
	return false;
}

bool f_plat(const Platform& p)
{
	/*
    for(int v:p.getAngleSorties()){
		if (v==0)
			return true;
	}
	*/
	return false;
}

bool f_true(const Platform& p)
{
    return true;
}

bool f_contientPoint(const Platform& p, Point point)
{
	// retourne true si une sortie permet d'atteindre le point 
	vector<Point> sortieMin = p.getSortieMin() ;
	vector<Point> sortieMax = p.getSortieMin() ;
	int n = sortieMin.size() ;
	for (int i = 0 ; i<n ; i++) {
		Point pmin = sortieMin[i] ;
		Point pmax = sortieMax[i] ;
		if (pmin.getX() <= point.getX() and point.getX() <= pmax.getX() and pmin.getY() <= point.getY() and point.getY() <= pmax.getY() and pmin.getZ() <= point.getZ() and point.getZ() <= pmax.getZ() and pmin.getK() <= point.getK() and point.getK() <= pmax.getK()) {
			return true ;
		}
	}
	return false;
}
