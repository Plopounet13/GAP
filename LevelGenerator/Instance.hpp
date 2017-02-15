#ifndef Instance_hpp
#define Instance_hpp

#include <vector>

class Position{
private:
	std::vector<float> pos;
	std::vector<float> rot;
	std::vector<float> scale;
	
public:
	Position(float x, float y, float z, float rx, float ry, float rz, float sx, float sy, float sz);
	friend Position operator- (const Position& a, const Position& b);
	friend ostream& operator<< (ostream& out, const Position& p);
};

class PlatInstance{
private:
	int ID;
	
	std::vector<Position> positions;
	std::vector<std::vector<float>> posSortie;
	std::vector<Position> pos4D;
	
public:
	PlatInstance(int id,
				 std::vector<Position> pos,
				 std::vector<std::vector<float>> posSortie,
				 std::vector<Position> pos4D);
	
	friend ostream& operator<< (ostream& out, const PlatInstance& p);
};

class Instance{
private:
	std::vector<PlatInstance*>
};

#endif /* Instance_hpp */
