#ifndef POLYNOME_H
#define POLYNOME_H

#include <vector>
#include <complex>
#include <iostream>

class Polynome{
// polynome a coefficients reels, initialise avec des reels

private:
	std::vector<long double> coefs;

public:
	Polynome();
	Polynome(Polynome const& p);
	Polynome(long double coefficient);
	Polynome(std::vector<long double> coefficients);
	std::complex<long double> eval(std::complex<long double> a) const;
	long double evalreel(long double a) const;
	int degre() const;
	std::vector<long double> durandkerner(long double epsilon = 0.0001) const;

friend std::ostream& operator<< (std::ostream& stream, Polynome const& p) ;
friend Polynome derive(Polynome const& p) ;
friend Polynome operator*(Polynome const& a, Polynome const& b) ;
friend Polynome operator+(Polynome const& a, Polynome const& b) ;
};





#endif /* POLYNOME_H */
