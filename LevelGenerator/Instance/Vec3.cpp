#include "Vec3.hpp"

using namespace std;

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
bool Vec3<T>::operator== (const Vec3<T>& b) const{
	return (x==b.x && y==b.y && z==b.z);
}

template class Vec3<int>;
template class Vec3<long>;
template class Vec3<long long>;
template class Vec3<float>;
template class Vec3<double>;
template class Vec3<long double>;
