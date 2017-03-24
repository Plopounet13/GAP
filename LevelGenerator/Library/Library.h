#ifndef LIBRARY_H
#define LIBRARY_H

#include <list>
#include <vector>
#include <cmath>
#include <functional>
#include "Platform.h"
#include "Point.h"

class Library{
private:
	std::list<Platform*> platList;
	
public:
	Library();
	void push(Platform* p); //Adds platform p at the end of the list.
	void select(std::function<bool(const Platform&)> f, std::vector<Platform*>& res) const;
};


// fonctions pour select

bool f_monte(const Platform& p) ;
bool f_descend(const Platform& p) ;
bool f_plat(const Platform& p) ;
bool f_true(const Platform& p) ;
bool f_ponctuelle(const Platform& p) ;
bool f_atteintPointRotation(const Platform& p, Point point, int rotation) ;
bool f_atteintPoint(const Platform& p, Point point) ;

#endif /* LIBRARY_H */
