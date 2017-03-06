#include "Instance.h"

using namespace std;

extern double PI_180;

Instance::Instance():plateformes(){}

void Instance::addPlatform(const PlatInstance& plat){
	plateformes.push_back(plat);
}

void Instance::rotate(const Vec3<float>& c, const Vec3<float>& dr){
	
	float cosx = cos(dr.getx()* PI_180);
	float cosy = cos(dr.gety()* PI_180);
	float cosz = cos(dr.getz()* PI_180);
	float sinx = sin(dr.getx()* PI_180);
	float siny = sin(dr.gety()* PI_180);
	float sinz = sin(dr.getz()* PI_180);
	
	for (auto& p:plateformes){
		p.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);
	}
}

void Instance::rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz){
	for (auto& p:plateformes){
		p.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);
	}
}

void Instance::translate(const Vec3<float>& d){
	for (auto& p:plateformes){
		p.translate(d);
	}
}

void Instance::rescale(const Vec3<float>& c,const Vec3<float>& ds){
	for (auto& p:plateformes){
		p.rescale(c, ds);
	}
}

//Warning empties Instance b;
Instance& operator+=(Instance& a, Instance& b){
	if(&a == &b){
		cerr << "Error: Instance operator a += b." << endl << "a and b must be different Instances" << endl;
		return a;
	}
		
	a.plateformes.splice(a.plateformes.end(), b.plateformes);
	return a;
}

ostream& operator<<(ostream& out, const Instance& i){
	out << i.plateformes.size() << endl;
	for (auto j=i.plateformes.begin(); j!=i.plateformes.end(); ++j){
		out << *j;
		if (++j!=i.plateformes.end())
			out << endl;
		--j;
	}
	
	return out;
}
