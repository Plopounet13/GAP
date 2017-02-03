#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <iostream>

class Point {
/// Cette classe défini les Points


public:
    Point();
    Point(int x, int y=0, int z=0, int k=0);
    Point(Point const& orig);
    int getX() const;
    int getY() const;
    int getZ() const;
    int getK() const;
    long double norm2() const ;
    long double norm3() const ;
    long double norm4() const ;
    virtual ~Point();
    
    
private:
    int m_x ;
    int m_y ;
    int m_z ;
    int m_k ;
    
    

friend Point operator-(Point const& a, Point const& b) ;
friend Point operator+(Point const& a, Point const& b) ;
friend std::ostream& operator<< (std::ostream& stream, Point const& point) ;
friend Point bound(Point const& a, Point const& minb, Point const& maxc) ;
friend long double dist2(Point const& a, Point const& b) ;
friend long double dist3(Point const& a, Point const& b) ;
friend long double dist4(Point const& a, Point const& b) ;
friend long double scal2(Point const& a, Point const& b) ;
friend long double scal3(Point const& a, Point const& b) ;
friend long double scal4(Point const& a, Point const& b) ;

};

#endif /* POINT_H */
