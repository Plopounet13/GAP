#ifndef Position_hpp
#define Position_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include "Vec3.hpp"

class Position{
	int k;
	Vec3<float> pos;
	Vec3<float> rot;
	Vec3<float> scale;
	
public:
	
	const Vec3<float>& getPos() const;
	
	Position(const Vec3<float>& loc, const Vec3<float>& rot, const Vec3<float>& scale);
	Position(float k, const Vec3<float>& loc, const Vec3<float>& rot, const Vec3<float>& scale);
	Position(const Position& p);
	
	void rotate(const Vec3<float>& dr);
	void translate(const Vec3<float>& d);
	void rescale(const Vec3<float>& ds);
	void rotate(const Vec3<float>& c, const Vec3<float>& dr);
	void rotate(const Vec3<float>& c, const Vec3<float>& dr, float cosx, float cosy, float cosz, float sinx, float siny, float sinz);
	void rescale(const Vec3<float>& c, const Vec3<float>& ds);
	
	friend Position operator- (const Position& a, const Position& b);
	friend std::ostream& operator<< (std::ostream& out, const Position& p);
};

#endif /* Instance_hpp */
