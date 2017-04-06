#include "geometrie.h"


Point::Point(){
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_length = 0;
}

Point::Point(const Point& p){
	m_x = p.m_x;
	m_y = p.m_y;
	m_z = p.m_z;
	m_length = p.m_length;
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

Point operator*(double lhs, const Point& rhs){
    Point res(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());
    return res;
}

Point operator*(const Point& rhs, double lhs){
    Point res(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z());
    return res;
}

Point operator+(const Point& lhs, const Point& rhs){
	Point res(lhs.x()+rhs.x(), lhs.y()+rhs.y(), lhs.z()+rhs.z());
	return res;
}

Point operator-(const Point& lhs, const Point& rhs){
	Point res(lhs.x()-rhs.x(), lhs.y()-rhs.y(), lhs.z()-rhs.z());
	return res;
}
