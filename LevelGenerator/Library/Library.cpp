#include "Library.h"

using namespace std;

#define PI 3.14159265

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

bool f_ponctuelle(const Platform& p)
{	
    return (p.getNbSorties()==0) ;
}

bool f_atteintPointRotation(const Platform& p, Point point, int rotation)
{
	// retourne true si, avec rotation donnee (en degree), une sortie permet d'atteindre le point 
	vector<Point> sortieMin = p.getSortieMin() ;
	vector<Point> sortieMax = p.getSortieMin() ;
	int n = sortieMin.size() ;
        long double x = point.getX() ;
        long double y = point.getY() ;
        long double r = sqrt(x*x+y*y) ;
        long double theta = atan2(y,x)*180/PI ;
        long double theta2 = theta - rotation*1.0 ;
        long double x2 = r*cos(theta2*PI/180);
        long double y2 = r*sin(theta2*PI/180);
	for (int i = 0 ; i<n ; i++) {
		Point pmin = sortieMin[i] ;
		Point pmax = sortieMax[i] ;
		if (pmin.getX() <= x2&&x2 <= pmax.getX()&&pmin.getY() <= y2&&y2 <= pmax.getY()&&pmin.getZ() <= point.getZ()&&point.getZ() <= pmax.getZ()&&pmin.getK() <= point.getK()&&point.getK() <= pmax.getK()) {
                	return true ;
		}
	}
	return false;
}

bool f_atteintPoint(const Platform& p, Point point)
{
	// retourne true si, avec rotation d'axe Z, une sortie permet d'atteindre le point 
	vector<Point> sortieMin = p.getSortieMin() ;
	vector<Point> sortieMax = p.getSortieMin() ;
	int n = sortieMin.size() ;
        long double x = point.getX() ;
        long double y = point.getY() ;
        long double r = sqrt(x*x+y*y) ;
        long double theta = atan2(y,x)*180/PI ;
        for (int i = 0 ; i<n ; i++) {
            Point pmin = sortieMin[i] ;
            Point pmax = sortieMax[i] ;
            for (int rot = 0 ; rot < 35 ; rot++) {
                long double theta2 = theta - rot*10.0 ;
                long double x2 = r*cos(theta2*PI/180);
                long double y2 = r*sin(theta2*PI/180);
                if (pmin.getX() <= x2&&x2 <= pmax.getX()&&pmin.getY() <= y2&&y2 <= pmax.getY()&&pmin.getZ() <= point.getZ()&&point.getZ() <= pmax.getZ()&&pmin.getK() <= point.getK()&&point.getK() <= pmax.getK()) {
                        return true ;
                }
            }
        }
	return false;
}
