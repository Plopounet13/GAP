#ifndef GEOMETRIE_H_INCLUDED
#define GEOMETRIE_H_INCLUDED
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#define vecteur point

class point{
/// Cette classe définit les points (et les vecteurs) dans l'espace à 3 dimensions

public:
    point();
    point(double a, double b, double c);
    const double x();
    const double y();
    const double z();
    const double length();
    void set(double a, double b, double c);
    void mult(double lambda);

private:
    double m_x, m_y, m_z, m_length;
};

#endif // GEOMETRIE_H_INCLUDED
