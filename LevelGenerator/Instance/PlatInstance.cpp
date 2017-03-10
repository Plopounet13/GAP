#include "PlatInstance.h"

extern double PI_180;

using namespace std;

PlatInstance::PlatInstance(int id,
						   const Position& p,
						   std::vector<Vec3<float>>& pS,
						   std::vector<float> s4D,
						   std::vector<Position>& p4,
						   int r):pos(p){
	sortie4D.swap(s4D);
	posSortie.swap(pS);
	pos4D.swap(p4);
	ID=id;
	rand=r;
	// On considère que la position donnée est la position de l'entrée de la plateforme
	// On doit donc décaler la position pour qu'elle soit celle du centre.
	// Le centre est considéré comme le milieu entre l'entrée et la première sortie.
	if (posSortie.size()){
		pos.translate((posSortie.front()-pos.getPos())/2);
	}
}

void PlatInstance::rotate(const Vec3<float>& dr){
	rotate(pos.getPos(), dr);
}

void PlatInstance::translate(const Vec3<float>& d){
	pos.translate(d);
	
	for (auto& p:posSortie){
		p+=d;
	}
	
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
		p+=(p-c)*(ds-1);
	
	for (auto& p:pos4D)
		p.rescale(c, ds);
}


void PlatInstance::rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz){
	
	pos.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);
	
	for (auto& p:posSortie){
		Vec3<float> d;
		d = p-c;
		
		float nx, ny, nz;
		float x=cosz*d.getx()-sinz*d.gety();
		float y=cosz*d.gety()+sinz*d.getx();
		float z=d.getz();
		
		nx=x;
		ny=cosx*y-sinx*z;
		nz=cosx*z+sinx*y;
		
		x=cosy*nx+siny*nz;
		y=ny;
		z=cosy*nz-siny*nx;
		
		p= c+Vec3<float>(x,y,z);
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
		Vec3<float> d;
		d = p-c;
		
		float nx, ny, nz;
		float x=cosz*d.getx()-sinz*d.gety();
		float y=cosz*d.gety()+sinz*d.getx();
		float z=d.getz();
		
		nx=x;
		ny=cosx*y-sinx*z;
		nz=cosx*z+sinx*y;
		
		x=cosy*nx+siny*nz;
		y=ny;
		z=cosy*nz-siny*nx;
		
		p= c+Vec3<float>(x,y,z);
	}
	
	for (auto& p:pos4D)
		p.rotate(c, dr, cosx, cosy, cosz, sinx, siny, sinz);
}

ostream& operator<< (ostream& out, const PlatInstance& p){
	out << p.ID << endl;
	out << p.rand << endl;
	out << p.pos << endl;
	out << p.posSortie.size() << endl;
	for(int i=0; i < int(p.posSortie.size()); ++i){
		out << p.posSortie[i]-p.pos.getPos() << endl;
		out << p.sortie4D[i] << endl;
	}
	cout << p.pos4D.size() << endl;
	for(int i=0; i<int(p.pos4D.size())-1; ++i){
		cout << p.pos4D[i]-p.pos << endl;
	}
	
	cout << p.pos4D.back()-p.pos;
	
	return out;
}
