#ifndef Library_hpp
#define Library_hpp

#include <list>
#include <vector>
#include <functional>
#include "Platform.h"

class Library{
private:
	std::list<Platform*> platList;
	
public:
	Library();
	void push(Platform* p); //Adds platform p at the end of the list.
	void select(std::function<bool(const Platform&)> f, std::vector<Platform*>& res) const;
};

#endif /* Library_hpp */
