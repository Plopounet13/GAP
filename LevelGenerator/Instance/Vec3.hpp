#ifndef Vec3_hpp
#define Vec3_hpp

#include <iostream>

template <class T>
class Vec3 {
	T x;
	T y;
	T z;
	
public:
	Vec3();
	Vec3(const Vec3<T>& v);
	Vec3(T v);
	Vec3(T mx, T my, T mz);
	
	T getx() const{
		return x;
	}
	
	T gety() const{
		return y;
	}
	
	T getz() const{
		return z;
	}
	
	T scalar(const Vec3<T>& b) const;
	//Vectorial product
	Vec3<T> operator^(const Vec3<T>& b) const;
	
	//Vector addition
	Vec3<T> operator+ (const Vec3<T>& b) const;
	Vec3<T> operator+ (const T& b) const;
	
	Vec3<T> operator- (const Vec3<T>& b) const;
	Vec3<T> operator- (const T& b) const;
	Vec3<T> operator- () const;
	//Coord to Coord Product
	Vec3<T> operator* (const Vec3<T>& b) const;
	Vec3<T> operator* (const T& b) const;
	
	Vec3<T> operator/ (const Vec3<T>& b) const;
	Vec3<T> operator/ (const T& b) const;
	
	Vec3<T>& operator+= (const Vec3<T>& b);
	Vec3<T>& operator+= (const T& b);
	
	Vec3<T>& operator-= (const Vec3<T>& b);
	Vec3<T>& operator-= (const T& b);
	
	Vec3<T>& operator/= (const Vec3<T>& b);
	Vec3<T>& operator/= (const T& b);
	
	Vec3<T>& operator*= (const Vec3<T>& b);
	Vec3<T>& operator*= (const T& b);
	
	bool operator== (const Vec3<T>& b) const;
	
	friend std::ostream& operator<< (std::ostream& out, const Vec3<T>& v){
		out << v.x << std::endl;
		out << v.y << std::endl;
		out << v.z;
		
		return out;
	}
	
	friend std::istream& operator>> (std::istream& in, Vec3<T>& v){
		in >> v.x >> v.y >> v.z;
		
		return in;
	}
};


#endif /* Vec3_hpp */
