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

long double Point::norm2() const {
    int carre = m_x*m_x + m_y*m_y;
    return sqrt(carre) ;
}

long double Point::norm3() const {
    int carre = m_x*m_x + m_y*m_y + m_z*m_z;
    return sqrt(carre) ;
}

long double Point::norm4() const {
    int carre = m_x*m_x + m_y*m_y + m_z*m_z + m_k*m_k;
    return sqrt(carre) ;
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

Point bound(Point const& a, Point const& minb, Point const& maxc){
    int ax = a.m_x;
    int ay = a.m_y;
    int az = a.m_z;
    int ak = a.m_k;
    if (minb.m_x > ax){
        ax = minb.m_x;
    }
    else if (maxc.m_x<ax){
        ax = maxc.m_x;
    }
    if (minb.m_y > ay){
        ay = minb.m_y;
    }
    else if (maxc.m_y<ay){
        ay = maxc.m_y;
    }
    if (minb.m_z > az){
        az = minb.m_z;
    }
    else if (maxc.m_z<az){
        az = maxc.m_z;
    }
    if (minb.m_k > ak){
        ak = minb.m_k;
    }
    else if (maxc.m_k<ak){
        ak = maxc.m_k;
    }
    return Point(ax,ay,az,ak);
}
    

std::ostream& operator<< (std::ostream& stream, Point const& point)
{
    stream << "(" << point.m_x << "," << point.m_y << "," << point.m_z << "," << point.m_k << ")" ;
    return stream;
}

long double dist2(Point const& a, Point const& b) {
    int x=a.m_x-b.m_x , y=a.m_y-b.m_y;
    int carre = x*x + y*y;
    return sqrt(carre) ;
}

long double dist3(Point const& a, Point const& b) {
    int x=a.m_x-b.m_x , y=a.m_y-b.m_y , z=a.m_z-b.m_z ;
    int carre = x*x + y*y + z*z ;
    return sqrt(carre) ;
}

long double dist4(Point const& a, Point const& b) {
    int x=a.m_x-b.m_x , y=a.m_y-b.m_y , z=a.m_z-b.m_z , k=a.m_k-b.m_k ;
    int carre = x*x + y*y + z*z + k*k ;
    return sqrt(carre) ;
}

long double scal2(Point const& a, Point const& b) {
    return a.m_x*b.m_x + a.m_y*b.m_y;
}

long double scal3(Point const& a, Point const& b) {
    return a.m_x*b.m_x + a.m_y*b.m_y + a.m_z*b.m_z;
}

long double scal4(Point const& a, Point const& b) {
    return a.m_x*b.m_x + a.m_y*b.m_y + a.m_z*b.m_z + a.m_k*b.m_k;
}
