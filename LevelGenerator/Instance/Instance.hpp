#ifndef Instance_hpp
#define Instance_hpp

#include <vector>
#include <iostream>
#include <cmath>
#include "Position.hpp"
#include "PlatInstance.hpp"

class Instance{
private:
	std::vector<PlatInstance*> plateformes;
	
public:
	Instance();
};

#endif /* Instance_hpp */
