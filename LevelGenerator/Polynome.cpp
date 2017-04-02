
#include "Polynome.h"
#define max(a,b) (a>b?a:b)

using namespace std;


// fonctions de la classe

Polynome::Polynome()
{
	coefs.resize(1) ;
	coefs[0] = 0 ;
}

Polynome::Polynome(Polynome const& p)
{
	int d = p.degre() ;
	coefs.resize(d) ;
	for (int i = 0 ; i<d ; i++) {
		coefs[i] = p.coefs[i] ;
	}
}

Polynome::Polynome(long double coefficient)
{
	coefs.resize(1) ;
	coefs[0] = coefficient ;
}

Polynome::Polynome(vector<long double> coefficients)
{
	int s = (int)coefficients.size() ;
	coefs.resize(s) ;
	for (int i=0 ; i<s ; i++) {
		coefs[i] = coefficients[i] ;
	}
}

complex<long double> Polynome::eval(complex<long double> a) const
{
	complex<long double> z ;
	int s = (int)coefs.size() ;
	if (s==0) {
		z = 0 ;
		return z ;
	}
	z = coefs[s-1] ;
	for (int i = s-2 ; i>=0 ; i--) {
		z *= a ;
		z += coefs[i] ;
	}
	return z ;
}

long double Polynome::evalreel(long double a) const
{
	long double z ;
	int s = (int)coefs.size() ;
	if (s==0) {
		z = 0 ;
		return z ;
	}
	z = coefs[s-1] ;
	for (int i = s-2 ; i>=0 ; i--) {
		z *= a ;
		z += coefs[i] ;
	}
	return z ;
}

int Polynome::degre() const
{
	int d = (int)coefs.size()-1 ;
	while (d>=1 && coefs[d]==0)
		d-- ;
	return d ;
}

vector<long double> Polynome::durandkerner(long double epsilon) const
{
	// renvoi toutes les racines reelles du polynome entre 0 et 1.
	int d = this->degre() ;
	vector<complex<long double>> rac, racbis ;
	rac.resize(d) ;
	racbis.resize(d) ;
	for (int i = 0 ; i<d ; i++) {
		rac[i] = polar(0.5, 2*3.1416/d*i+0.16) ;
	}
	
	bool termine = false ;
	while (! termine) {
		for (int i = 0 ; i<d ; i++) {
			complex<long double> r = rac[i] ;
			complex<long double> temp = 1 ;
			for (int j = 0 ; j<d ; j++) {
				if (i!=j)
					temp *= (r-rac[j]) ;
			}
			temp *= coefs[d] ;
			racbis[i] = r - this->eval(r)/temp ;
		}
		termine = true ;
		for (int i = 0 ; i<d && termine; i++) {
			if (abs(rac[i]-racbis[i]) >= epsilon)
				termine = false ;
		}
		for (int i = 0 ; i<d ; i++) {
			rac[i] = racbis[i] ;
		}
	}
	
	vector<long double> v ;
	for (int i=0 ; i<d ; i++) {
		long double r = real(rac[i]) ;
		if (abs(imag(rac[i]))<10*epsilon && r>=0 && r<=1)
			v.push_back(r) ;
	}
	return v ;
}

// fonctions friend


ostream& operator<< (ostream& stream, Polynome const& p)
{
	stream << "[" ;
	int i ;
	for (i = 0 ; i+1 < int(p.coefs.size()) ; i++) {
		stream << p.coefs[i] << "," ;
	}
	stream << p.coefs[i] << "]" ;
    return stream;
}

Polynome derive(Polynome const& p)
{
	int d = p.degre() ;
	if (d==0)
		return Polynome() ;
	vector<long double> v ;
	v.resize(d) ;
	for (int i = 1 ; i<=d ; i++) {
		v[i-1] = i*p.coefs[i] ;
	}
	return Polynome(v) ;
}

Polynome operator*(Polynome const& a, Polynome const& b) {
	vector<long double> v ;
    int da = a.degre();
    int db = b.degre();
    int d = da+db ;
    v.resize(d+1) ;
    for (int i = 0 ; i<=d ; i++)
    	v[i] = 0 ;
    for (int i = 0 ; i<=da ; i++) {
    	for (int j = 0 ; j<=db ; j++) {
    		v[i+j] += a.coefs[i]*b.coefs[j] ;
    	}
    }
    return Polynome(v) ;
}

Polynome operator+(Polynome const& a, Polynome const& b) {
    vector<long double> v ;
    int d = max(a.degre(),b.degre()) ;
    v.resize(d+1) ;
    for (int i = 0 ; i<=d ; i++)
    	v[i] = 0 ;
    for (int i = 0 ; i<=a.degre() ; i++) {
    	v[i] += a.coefs[i] ;
    }
    for (int i = 0 ; i<=b.degre() ; i++) {
    	v[i] += b.coefs[i] ;
    }
    return Polynome(v) ;
}
