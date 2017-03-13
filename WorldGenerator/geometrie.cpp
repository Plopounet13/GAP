#include "geometrie.h"


Point::Point(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_length = 0;
}

Point::Point(double a, double b, double c) : m_x(a), m_y(b), m_z(c) {
    m_length = std::sqrt(a*a + b*b + c*c);
}

double Point::x() const{
    return m_x;
}

double Point::y() const{
    return m_y;
}

double Point::z() const{
    return m_z;
}

double Point::length()const{
    return m_length;
}

void Point::set(double a, double b, double c){
    m_x = a, m_y = b, m_z = c, m_length = std::sqrt(a*a + b*b + c*c);
}

void Point::mult(double lambda){
    m_x *= lambda, m_y *= lambda, m_z *= lambda, m_length *= lambda;
}

Point operator*(double lhs, Point rhs){
    rhs.set(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());
    return rhs;
}

Point operator*(Point rhs, double lhs){
    rhs.set(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());
    return rhs;
}

Point operator+(Point lhs, const Point& rhs){
    lhs.set(lhs.x()+rhs.x(), lhs.y()+rhs.y(), lhs.z()+rhs.z());
    return lhs;
}
