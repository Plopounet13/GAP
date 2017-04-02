#ifndef POINT4_H
#define POINT4_H

#include <cmath>
#include <iostream>
#include "../../WorldGenerator/geometrie.h"

class Point4 {
/// Cette classe défini les Points


public:
    Point4();
    Point4(int x, int y=0, int z=0, int k=0);
	Point4(Point4 const& orig);
	Point4(Point const& orig);
    int getX() const;
    int getY() const;
    int getZ() const;
    int getK() const;
    long double norm2() const ;
    long double norm3() const ;
    long double norm4() const ;
    virtual ~Point4();
    
    
private:
    int m_x ;
    int m_y ;
    int m_z ;
    int m_k ;
    
    

friend Point4 operator-(Point4 const& a, Point4 const& b) ;
friend Point4 operator+(Point4 const& a, Point4 const& b) ;
friend std::ostream& operator<< (std::ostream& stream, Point4 const& point) ;
friend Point4 bound(Point4 const& a, Point4 const& minb, Point4 const& maxc) ;
friend long double dist2(Point4 const& a, Point4 const& b) ;
friend long double dist3(Point4 const& a, Point4 const& b) ;
friend long double dist4(Point4 const& a, Point4 const& b) ;
friend long double scal2(Point4 const& a, Point4 const& b) ;
friend long double scal3(Point4 const& a, Point4 const& b) ;
friend long double scal4(Point4 const& a, Point4 const& b) ;
	friend void fromPoint(const Point& p, Point4& out);
};

#endif /* POINT4_H */
