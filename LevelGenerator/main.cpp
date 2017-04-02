#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <time.h>
#include <algorithm>
#include <complex>
#include "Library/Point4.h"
#include "Library/Platform.h"
#include "Library/Library.h"
#include "Instance/Instance.h"
#include "Instance/PlatInstance.h"
#include "Instance/Position.h"
#include "Instance/Vec3.h"
#include "Polynome.h"
#include "levelGenerator.h"

using namespace std;

#define PI 3.14159265

int main(int argc, char** argv)
{
	
	Library bibli ;
	
	
	filebuf fb;
	
	for(int i=0 ; i < 10 ; i++) {
		if (fb.open ("Library/p"+to_string(i)+".txt",ios::in))
		{
			istream is(&fb);
			Platform *p = new Platform(is) ;
			bibli.push(p) ;
			
			fb.close();
		}
		else {
			cerr << "Failed" << endl ;
		}
	}
	
	
	
	Point4 entree = Point4(100,100,20,200);
	Point4 sortie = Point4(10000,10000,800,1600);
	Instance parcours;
	generationLocale(bibli, entree, sortie, 11000, 11000, 2000, parcours);
	cout << parcours;
	
}

