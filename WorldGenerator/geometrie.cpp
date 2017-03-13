#include "geometrie.h"


point::point(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_length = 0;
}

point::point(double a, double b, double c) : m_x(a), m_y(b), m_z(c) {
    m_length = std::sqrt(a*a + b*b + c*c);
}

double point::x() const{
    return m_x;
}

double point::y() const{
    return m_y;
}

double point::z() const{
    return m_z;
}

double point::length()const{
    return m_length;
}

void point::set(double a, double b, double c){
    m_x = a, m_y = b, m_z = c, m_length = std::sqrt(a*a + b*b + c*c);
}

void point::mult(double lambda){
    m_x *= lambda, m_y *= lambda, m_z *= lambda, m_length *= lambda;
}

point operator*(double lhs, point rhs){
    rhs.set(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());
    return rhs;
}

point operator*(point rhs, double lhs){
    rhs.set(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());
    return rhs;
}

point operator+(point lhs, const point& rhs){
    lhs.set(lhs.x()+rhs.x(), lhs.y()+rhs.y(), lhs.z()+rhs.z());
    return lhs;
}
