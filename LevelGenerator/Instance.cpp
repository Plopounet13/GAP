#include "Instance.hpp"

Position::Position(float x, float y, float z,
				   float rx, float ry, float rz,
				   float sx, float sy, float sz):pos(3), rot(3), scale(3){
	pos[0]=x;
	pos[0]=y;
	pos[0]=z;
	
	rot[0]=rx;
	rot[0]=ry;
	rot[0]=rz;
	
	scale[0]=sx;
	scale[0]=sy;
	scale[0]=sz;
}

Position operator- (const Position& a, const Position& b){
	Position p(a.pos[0]-b.pos[0], a.pos[1]-b.pos[1], a.pos[2]-b.pos[2],
			   a.rot[0]-b.rot[0], a.rot[1]-b.rot[1], a.rot[2]-b.rot[2],
			   a.scale[0]-b.scale[0], a.scale[1]-b.scale[1], a.scale[2]-b.scale[2]);
	return p;
}

friend ostream& operator<< (ostream& out, const Position& p){
	
	for (float& f:pos){
		out << f << endl;
	}
	
	for (float& f:rot){
		out << f << endl;
	}
	
	for (float& f:scale){
		out << f << endl;
	}
}


PlatInstance::PlatInstance(int id,
						   std::vector<Position> pos,
						   std::vector<std::vector<float>> posSortie,
						   std::vector<Position> pos4D):positions(pos),
														posSortie(posSortie),
														pos4D(pos4D){
	ID=id;
};
