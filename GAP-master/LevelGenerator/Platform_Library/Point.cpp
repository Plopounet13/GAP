#include "Point.h"


//// Focntions de la classe


Point::Point() : m_x(0) , m_y(0) , m_z(0) , m_k(0)
{
}

Point::Point(int x, int y, int z, int k) : m_x(x) , m_y(y) , m_z(z) , m_k(k)
{
}

Point::Point(Point const& orig) {
    m_x = orig.m_x ;
    m_y = orig.m_y ;
    m_z = orig.m_z ;
    m_k = orig.m_k ;
}

int Point::getX() const {
    return m_x ;
}

int Point::getY() const {
    return m_y ;
}

int Point::getZ() const {
    return m_z ;
}

int Point::getK() const {
    return m_k ;
}

Point::~Point() {
}



//// Fonctions Friend

Point operator+(Point const& a, Point const& b) {
    return Point(a.m_x+b.m_x, a.m_y+b.m_y, a.m_z+b.m_z, a.m_k+b.m_k);
}

Point operator-(Point const& a, Point const& b) {
    return Point(a.m_x-b.m_x, a.m_y-b.m_y, a.m_z-b.m_z, a.m_k-b.m_k);
}

std::ostream& operator<< (std::ostream& stream, Point const& point)
{
    stream << "(" << point.m_x << "," << point.m_y << "," << point.m_z << "," << point.m_k << ")" ;
    return stream;
}

float dist2(Point const& a, Point const& b) {
    int x=a.m_x-b.m_x , y=a.m_y-b.m_y;
    int carre = x*x + y*y;
    return sqrt(carre) ;
}

float dist3(Point const& a, Point const& b) {
    int x=a.m_x-b.m_x , y=a.m_y-b.m_y , z=a.m_z-b.m_z ;
    int carre = x*x + y*y + z*z ;
    return sqrt(carre) ;
}

float dist4(Point const& a, Point const& b) {
    int x=a.m_x-b.m_x , y=a.m_y-b.m_y , z=a.m_z-b.m_z , k=a.m_k-b.m_k ;
    int carre = x*x + y*y + z*z + k*k ;
    return sqrt(carre) ;
}

float norm2(Point const& a) {
    int x=a.m_x, y=a.m_y;
    int carre = x*x + y*y;
    return sqrt(carre) ;
}

float norm3(Point const& a) {
    int x=a.m_x, y=a.m_y, z=a.m_z;
    int carre = x*x + y*y + z*z;
    return sqrt(carre) ;
}

float norm4(Point const& a) {
    int x=a.m_x, y=a.m_y, z=a.m_z, k=a.m_k ;
    int carre = x*x + y*y + z*z + k*k ;
    return sqrt(carre) ;
}

