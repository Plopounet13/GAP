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

const double point::x(){
    return m_x;
}

const double point::y(){
    return m_y;
}

const double point::z(){
    return m_z;
}

const double point::length(){
    return m_length;
}

void point::set(double a, double b, double c){
    m_x = a, m_y = b, m_z = c, m_length = std::sqrt(a*a + b*b + c*c);
}

void point::mult(double lambda){
    m_x *= lambda, m_y *= lambda, m_z *= lambda, m_length *= lambda;
}
