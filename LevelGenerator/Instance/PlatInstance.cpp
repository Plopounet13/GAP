#include <algorithm>
#include "PlatInstance.h"

extern double PI_180;

using namespace std;

bool compare4D(const Position& a, const Position& b){
	return (a.k < b.k);
}

PlatInstance::PlatInstance(int id,
						   const Position& p,
						   std::vector<Vec3<float>>& pS,
						   std::vector<float> s4D,
						   std::vector<Position>& p4,
						   int r):pos(p){
	if (!pos.kset())
		cerr << "Erreur: la plateforme n'a pas de position 4D d'entrée" << endl;
	sortie4D.swap(s4D);
	posSortie.swap(pS);
	pos4D.swap(p4);
	sort(pos4D.begin(), pos4D.end(), compare4D);
	ID=id;
	rand=r;
}

void PlatInstance::rotate(const Vec3<float>& dr){
	rotate(pos.getPos(), dr);
}

void PlatInstance::translate(const Vec3<float>& d){
	pos.translate(d);

	for (auto& p:pos4D){
		p.translate(d);
	}
}

void PlatInstance::rescale(const Vec3<float>& ds){
	rescale(pos.getPos(), ds);
}

void PlatInstance::rescale(const Vec3<float>& c, const Vec3<float>& ds){
	pos.rescale(c, ds);

	for (auto& p:posSortie)
		p *= ds;

	for (auto& p:pos4D)
		p.rescale(c, ds);
}


void PlatInstance::rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz){

	pos.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);

	for (auto& p:posSortie){
		p.rotate(cosx, cosy, cosz, sinx, siny, sinz);
	}

	for (auto& p:pos4D)
		p.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);
}

void PlatInstance::rotate(const Vec3<float>& c, const Vec3<float>& dr){

	float cosx = cos(dr.getx()* PI_180);
	float cosy = cos(dr.gety()* PI_180);
	float cosz = cos(dr.getz()* PI_180);
	float sinx = sin(dr.getx()* PI_180);
	float siny = sin(dr.gety()* PI_180);
	float sinz = sin(dr.getz()* PI_180);

	pos.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);

	for (auto& p:posSortie){
		p.rotate(cosx, cosy, cosz, sinx, siny, sinz);
	}

	for (auto& p:pos4D)
		p.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);
}


//TODO: change output in order to allow no pos4D
ostream& operator<< (ostream& out, const PlatInstance& p){
    //out << "________________" << endl;
	out << p.ID << endl;
	out << ((float)p.rand/(float)RAND_MAX) << endl;
	out << p.pos << endl;
	out << p.posSortie.size() << endl;
	for(int i=0; i < int(p.posSortie.size()); ++i){
		out << p.posSortie[i] << endl;
		out << p.sortie4D[i] << endl;
	}
	
	out << p.pos4D.size() << endl;
	for(int i=0; i<int(p.pos4D.size())-1; ++i){
		out << p.pos4D[i]-p.pos << endl;
	}

	out << p.pos4D.back()-p.pos;

	return out;
}
