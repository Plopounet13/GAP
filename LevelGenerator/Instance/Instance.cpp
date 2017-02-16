#include "Instance.hpp"

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

void Instance::rescale(const Vec3<float> c,const Vec3<float>& ds){
	for (auto& p:plateformes){
		p.rescale(c, ds);
	}
}

Instance operator+(const Instance& a, const Instance& b){
	Instance i;
	for (auto& p:a.plateformes){
		i.addPlatform(p);
	}
	for (auto& p:b.plateformes){
		i.addPlatform(p);
	}
	return i;
}

Instance& operator+=(Instance& a, const Instance& b){
	for (auto& p:b.plateformes){
		a.addPlatform(p);
	}
	return a;
}
