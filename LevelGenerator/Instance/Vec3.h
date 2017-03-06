#ifndef Vec3_h
#define Vec3_h

#include <iostream>

template <class T>
class Vec3 {
	T x;
	T y;
	T z;
	
public:
	Vec3();
	Vec3(const Vec3<T>& v);
	Vec3(T v);
	Vec3(T mx, T my, T mz);
	
	T getx() const{
		return x;
	}
	
	T gety() const{
		return y;
	}
	
	T getz() const{
		return z;
	}
	
	/**
	 * Calcule le produit scalaire avec b
	 */
	T scalar(const Vec3<T>& b) const;
	
	/**
	 * Opérateur de produit vectoriel
	 */
	Vec3<T> operator^(const Vec3<T>& b) const;
	
	
	/**
	 * Opérateur d'addition vecteur/vecteur
	 */
	Vec3<T> operator+ (const Vec3<T>& b) const;
	
	/**
	 * Opérateur d'addition vecteur/scalaire
	 * Ajoute le scalaire à chaque coordonnée.
	 */
	Vec3<T> operator+ (const T& b) const;
	
	/**
	 * Opérateur de soustraction vecteur/vecteur
	 */
	Vec3<T> operator- (const Vec3<T>& b) const;
	
	/**
	 * Opérateur de soustraction vecteur/scalaire
	 * Soustrait le scalaire à chaque coordonnée.
	 */
	Vec3<T> operator- (const T& b) const;
	
	/**
	 * Opérateur d'opposé
	 */
	Vec3<T> operator- () const;
	
	/**
	 * Opérateur de multiplication vecteur/vecteur
	 * Multiplie les coordonnées une à une.
	 */
	Vec3<T> operator* (const Vec3<T>& b) const;
	
	/**
	 * Opérateur de multiplication vecteur/scalaire
	 * Multiplie par le scalaire chaque coordonnée.
	 */
	Vec3<T> operator* (const T& b) const;
	
	/**
	 * Opérateur de division vecteur/vecteur
	 * Divise les coordonnées une à une.
	 */
	Vec3<T> operator/ (const Vec3<T>& b) const;
	
	/**
	 * Opérateur de division vecteur/scalaire
	 * Divise par le scalaire chaque coordonnée.
	 */
	Vec3<T> operator/ (const T& b) const;
	
	/**
	 * Opérateur d'addition vecteur/vecteur
	 */
	Vec3<T>& operator+= (const Vec3<T>& b);
	
	/**
	 * Opérateur d'addition vecteur/scalaire
	 * Ajoute le scalaire à chaque coordonnée.
	 */
	Vec3<T>& operator+= (const T& b);
	
	/**
	 * Opérateur de soustraction vecteur/vecteur
	 */
	Vec3<T>& operator-= (const Vec3<T>& b);
	
	/**
	 * Opérateur de soustraction vecteur/scalaire
	 * Soustrait le scalaire à chaque coordonnée.
	 */
	Vec3<T>& operator-= (const T& b);
	
	/**
	 * Opérateur de division vecteur/vecteur
	 * Divise les coordonnées une à une.
	 */
	Vec3<T>& operator/= (const Vec3<T>& b);
	
	/**
	 * Opérateur de division vecteur/scalaire
	 * Divise par le scalaire chaque coordonnée.
	 */
	Vec3<T>& operator/= (const T& b);
	
	/**
	 * Opérateur de multiplication vecteur/vecteur
	 * Multiplie les coordonnées une à une.
	 */
	Vec3<T>& operator*= (const Vec3<T>& b);
	
	/**
	 * Opérateur de multiplication vecteur/scalaire
	 * Multiplie par le scalaire chaque coordonnée.
	 */
	Vec3<T>& operator*= (const T& b);
	
	/**
	 * Opérateur de comparaison vecteur/vecteur
	 * Deux vecteurs sont égaux si leurs coordonnées sont égales une à une.
	 */
	bool operator== (const Vec3<T>& b) const;
	
	/**
	 * Opérateur d'affichage d'un vecteur
	 * Print une coordonnée par ligne.
	 */
	friend std::ostream& operator<< (std::ostream& out, const Vec3<T>& v){
		out << v.x << std::endl;
		out << v.y << std::endl;
		out << v.z;
		
		return out;
	}
	
	/**
	 * Opérateur de lecture d'un vecteur
	 * Lis les coordonnées sur le stream.
	 */
	friend std::istream& operator>> (std::istream& in, Vec3<T>& v){
		in >> v.x >> v.y >> v.z;
		
		return in;
	}
};


#endif /* Vec3_h */
