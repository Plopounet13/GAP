#include "Vec3.h"

using namespace std;

extern double PI_180;

template <class T>
Vec3<T>::Vec3(T mx, T my, T mz){
	x=mx;
	y=my;
	z=mz;
}

template <class T>
Vec3<T>::Vec3(const Vec3<T>& v){
	x=v.x;
	y=v.y;
	z=v.z;
}

template <class T>
Vec3<T>::Vec3(const Point& p){
	x = p.x();
	y = p.y();
	z = p.z();
}

template <class T>
Vec3<T>::Vec3(T v){
	x=v;
	y=v;
	z=v;
}

template <class T>
T Vec3<T>::scalar(const Vec3<T>& b) const{
	return x*b.x + y*b.y + z*b.z;
}

template <class T>
Vec3<T> Vec3<T>::operator^(const Vec3<T>& b) const{
	Vec3<T> ret(y*b.z-z*b.y, x*b.z-z*b.x, x*b.y-y*b.x);
	return ret;
}

template <class T>
Vec3<T>::Vec3(){
	x=y=z=0;
}

template <class T>
Vec3<T> Vec3<T>::operator+ (const Vec3<T>& b) const{
	Vec3<T> res(x+b.x, y+b.y, z+b.z);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator+ (const T& b) const{
	Vec3<T> res(x+b, y+b, z+b);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator- (const Vec3<T>& b) const{
	Vec3<T> res(x-b.x, y-b.y, z-b.z);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator- (const T& b) const{
	Vec3<T> res(x-b, y-b, z-b);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator- () const{
	Vec3<T> res(-x, -y, -z);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator* (const Vec3<T>& b) const{
	Vec3<T> res(x*b.x, y*b.y, z*b.z);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator* (const T& b) const{
	Vec3<T> res(x*b, y*b, z*b);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator/ (const Vec3<T>& b) const{
	Vec3<T> res(x/b.x, y/b.y, z/b.z);
	return res;
}

template <class T>
Vec3<T> Vec3<T>::operator/ (const T& b) const{
	Vec3<T> res(x/b, y/b, z/b);
	return res;
}

template <class T>
Vec3<T>& Vec3<T>::operator+= (const Vec3<T>& b){
	x+=b.x;
	y+=b.y;
	z+=b.z;
	return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator+= (const T& b){
	x+=b;
	y+=b;
	z+=b;
	return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator-= (const Vec3<T>& b){
	x-=b.x;
	y-=b.y;
	z-=b.z;
	return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator-= (const T& b){
	x-=b;
	y-=b;
	z-=b;
	return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator*= (const Vec3<T>& b){
	x*=b.x;
	y*=b.y;
	z*=b.z;

	return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator*= (const T& b){
	x*=b;
	y*=b;
	z*=b;

	return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator/= (const Vec3<T>& b){
	x/=b.x;
	y/=b.y;
	z/=b.z;

	return *this;
}

template <class T>
Vec3<T>& Vec3<T>::operator/= (const T& b){
	x/=b;
	y/=b;
	z/=b;

	return *this;
}

template <class T>
void Vec3<T>::rotate(const Vec3<float>& dr){

	float cosx = cos(dr.getx()* PI_180);
	float cosy = cos(dr.gety()* PI_180);
	float cosz = cos(dr.getz()* PI_180);
	float sinx = sin(dr.getx()* PI_180);
	float siny = sin(dr.gety()* PI_180);
	float sinz = sin(dr.getz()* PI_180);

	rotate(cosx, cosy, cosz, sinx, siny, sinz);

}

template <class T>
void Vec3<T>::rotate(float cosx, float cosy, float cosz, float sinx, float siny, float sinz){

	float nx, ny, nz;
	nx = x;
	ny = cosx*y - sinx*z;
	nz = cosx*z + sinx*y;

	x=cosy*nx+siny*nz;
	y=ny;
	z=cosy*nz-siny*nx;

	nx = cosz*x - sinz*y;
	ny = cosz*y + sinz*x;
	nz = z;

	x = nx;
	y = ny;
	z = nz;
}

template <class T>
bool Vec3<T>::operator== (const Vec3<T>& b) const{
	return (x==b.x && y==b.y && z==b.z);
}

template class Vec3<int>;
template class Vec3<long>;
template class Vec3<long long>;
template class Vec3<float>;
template class Vec3<double>;
template class Vec3<long double>;
