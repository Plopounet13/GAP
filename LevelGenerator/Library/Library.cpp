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

bool f_atteintPointViaI(const Platform& p, Point4 point, int i)
{
	// retourne true si, avec rotation d'axe Z, la sorite i permet d'atteindre le point 
	vector<Point4> sortieMin = p.getSortieMin() ;
	vector<Point4> sortieMax = p.getSortieMax() ;
	long double x = point.getX() ;
	long double y = point.getY() ;
	long double r2 = x*x+y*y ;
        Point4 pmin = sortieMin[i] ;
        Point4 pmax = sortieMax[i] ;
        if (pmin.getZ() <= point.getZ()&&point.getZ() <= pmax.getZ()&&pmin.getK() <= point.getK()&&point.getK() <= pmax.getK()) {
            int xmin=pmin.getX(), ymin=pmin.getY(), xmax=pmax.getX(), ymax=pmax.getY() ;
            int xmin2=xmin*xmin, ymin2=ymin*ymin, xmax2=xmax*xmax, ymax2=ymax*ymax ;
            int x2_petit = min(xmin2,xmax2), x2_grand = max(xmin2,xmax2), y2_petit = min(ymin2,ymax2), y2_grand = max(ymin2,ymax2) ;
            int d_inf = x2_petit + y2_petit ;
            int d_sup = x2_grand + y2_grand ;
            if (d_inf <= r2 && r2 <= d_sup) {
                return true ;
            }
        }
	return false;
}


bool f_atteintPoint(const Platform& p, Point4 point)
{
	// retourne true si, avec rotation d'axe Z, une sortie permet d'atteindre le point 
	vector<Point4> sortieMin = p.getSortieMin() ;
	vector<Point4> sortieMax = p.getSortieMax() ;
	int n = (int)sortieMin.size() ;
	long double x = point.getX() ;
	long double y = point.getY() ;
	long double r2 = x*x+y*y ;
	for (int i = 0 ; i<n ; i++) {
            Point4 pmin = sortieMin[i] ;
            Point4 pmax = sortieMax[i] ;
            if (pmin.getZ() <= point.getZ()&&point.getZ() <= pmax.getZ()&&pmin.getK() <= point.getK()&&point.getK() <= pmax.getK()) {
                int xmin=pmin.getX(), ymin=pmin.getY(), xmax=pmax.getX(), ymax=pmax.getY() ;
                int xmin2=xmin*xmin, ymin2=ymin*ymin, xmax2=xmax*xmax, ymax2=ymax*ymax ;
                int x2_petit = min(xmin2,xmax2), x2_grand = max(xmin2,xmax2), y2_petit = min(ymin2,ymax2), y2_grand = max(ymin2,ymax2) ;
                int d_inf = x2_petit + y2_petit ;
                int d_sup = x2_grand + y2_grand ;
                if (d_inf <= r2 && r2 <= d_sup) {
                    return true ;
                }
            }
	}
	return false;
}
