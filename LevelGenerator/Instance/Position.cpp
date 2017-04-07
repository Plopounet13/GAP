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
		out << p.k << endl;
	}

	out << p.rot << endl;

	out << p.scale;

	return out;
}

void mult_matrix3(const vector<vector<float>>& M1, const vector<vector<float>>& M2, vector<vector<float>>& Mout){
    Mout = vector<vector<float>> (3, vector<float> (3, 0));
    for(int i = 0; i<3; ++i) for(int j = 0; j<3; ++j) for(int k = 0; k<3; ++k){
        Mout[i][k] += M1[i][k]*M2[k][j];
    }
}

void rotation_matrix(vector<vector<float>>& M, float cosx, float cosy, float cosz, float sinx, float siny, float sinz){
    M = vector<vector<float>> (3, vector<float> (3));
    M[0][0] = cosz*cosy;
    M[1][0] = sinz*cosy;
    M[2][0] = -siny;
    M[0][1] = cosz*siny*sinx-sinz*cosx;
    M[1][1] = sinz*siny*sinx+cosz*cosx;
    M[2][1] = cosy*sinx;
    M[0][2] = cosz*siny*cosx+sinz*sinx;
    M[1][2] = sinz*siny*cosx-cosz*sinx;
    M[2][2] = cosy*cosx;
}

void Position::rotate(const Vec3<float>& dr){
	float cosx = cos(dr.getx()* PI_180);
	float cosy = cos(dr.gety()* PI_180);
	float cosz = cos(dr.getz()* PI_180);
	float sinx = sin(dr.getx()* PI_180);
	float siny = sin(dr.gety()* PI_180);
	float sinz = sin(dr.getz()* PI_180);
	float cosx_prev = cos(rot.getx()* PI_180);
	float cosy_prev = cos(rot.gety()* PI_180);
	float cosz_prev = cos(rot.getz()* PI_180);
	float sinx_prev = sin(rot.getx()* PI_180);
	float siny_prev = sin(rot.gety()* PI_180);
	float sinz_prev = sin(rot.getz()* PI_180);
    vector<vector<float>>   Madd, Mold, Mnew;
    rotation_matrix(Madd, cosx, cosy, cosz, sinx, siny, sinz);
    rotation_matrix(Mold, cosx_prev, cosy_prev, cosz_prev, sinx_prev, siny_prev, sinz_prev);
	mult_matrix3(Madd, Mold, Mnew);
    float alpha, beta, gamma;
    alpha = atan2(Mnew[1][0], Mnew[0][0]);
    beta = atan2(-Mnew[2][0], sqrt(Mnew[2][1]*Mnew[2][1]+Mnew[2][2]*Mnew[2][2]));
    gamma = atan2(Mnew[2][1], Mnew[2][2]);
    rot = Vec3<float>(gamma, beta, alpha);
}

void Position::translate(const Vec3<float>& d){
	pos+=d;
}

void Position::rescale(const Vec3<float>& ds){
	scale*=ds;
}

void Position::rotate(const Vec3<float>& c, const Vec3<float>& dr){
	float cosx = cos(dr.getx()* PI_180);
	float cosy = cos(dr.gety()* PI_180);
	float cosz = cos(dr.getz()* PI_180);
	float sinx = sin(dr.getx()* PI_180);
	float siny = sin(dr.gety()* PI_180);
	float sinz = sin(dr.getz()* PI_180);

    rotate(c,dr,cosx,cosy,cosz,sinx,siny,sinz);
}

void Position::rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz){
	Vec3<float> d;
	d = pos-c;

	d.rotate(cosx, cosy, cosz, sinx, siny, sinz);

	pos = c+d;

	rotate(dr);
}

void Position::rescale(const Vec3<float>& c, const Vec3<float>& ds){
	pos+=(pos-c)*(ds-1);
	scale*=ds;
}

