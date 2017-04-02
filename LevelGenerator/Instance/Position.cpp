#include "Position.h"

using namespace std;


#define PI 3.14159265
double PI_180 = PI/180;

Position::Position(const Vec3<float>& loc, const Vec3<float>& r, const Vec3<float>& s){
	k=-1;
	
	pos=loc;
	
	rot=r;
	
	scale=s;
}

Position::Position(float mk, const Vec3<float>& loc, const Vec3<float>& r, const Vec3<float>& s){
	k=mk;
	
	pos=loc;
	
	rot=r;
	
	scale=s;
}

Position::Position(const Position& p){
	k=p.k;
	pos=p.pos;
	rot=p.rot;
	scale=p.scale;
}

Position::Position(){}

bool Position::kset(){
		return k!=-1;
}

const Vec3<float>& Position::getPos() const{
	return pos;
}

Position operator- (const Position& a, const Position& b){
	Position p(a.k, a.pos-b.pos, a.rot-b.rot, (b.scale==Vec3<float>(0))?Vec3<float>(1):a.scale/b.scale);
	return p;
}

ostream& operator<< (ostream& out, const Position& p){
	
	out << p.pos << endl;
	if (p.k!=-1){
		cout << p.k << endl;
	}
	
	out << p.rot << endl;
	
	out << p.scale;
	
	return out;
}

void Position::rotate(const Vec3<float>& dr){
	rot+=dr;
}

void Position::translate(const Vec3<float>& d){
	pos+=d;
}

void Position::rescale(const Vec3<float>& ds){
	scale*=ds;
}

void Position::rotate(const Vec3<float>& c, const Vec3<float>& dr){
	Vec3<float> d;
	d = pos-c;
	
	float cosx = cos(dr.getx()* PI_180);
	float cosy = cos(dr.gety()* PI_180);
	float cosz = cos(dr.getz()* PI_180);
	float sinx = sin(dr.getx()* PI_180);
	float siny = sin(dr.gety()* PI_180);
	float sinz = sin(dr.getz()* PI_180);
	
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
	
	pos= c+Vec3<float>(x,y,z);
	
	rot+=dr;
}

void Position::rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz){
	Vec3<float> d;
	d = pos-c;
	
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
	
	pos= c+Vec3<float>(x,y,z);
	
	rot+=dr;
}

void Position::rescale(const Vec3<float>& c, const Vec3<float>& ds){
	pos+=(pos-c)*(ds-1);
	scale*=ds;
}

