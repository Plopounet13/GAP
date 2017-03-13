#ifndef GEOMETRIE_H_INCLUDED
#define GEOMETRIE_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#define Vecteur Point

class Point{
/// Cette classe définit les points (et les vecteurs) dans l'espace à 3 dimensions

public:
    Point();
    Point(double a, double b, double c);
    double x() const;
    double y() const;
    double z() const;
    double length() const;
    void set(double a, double b, double c);
    void mult(double lambda);
    friend Point operator*(double lhs, const Point& rhs);
    friend Point operator*(const Point& rhs, double lhs);
    friend Point operator+(Point lhs, const Point& rhs);

private:
    double m_x, m_y, m_z, m_length;
};

#endif // GEOMETRIE_H_INCLUDED
