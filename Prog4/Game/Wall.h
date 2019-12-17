#pragma once
#include "Square.h"
class Wall : public Square {
public:
	Wall() {}; 
	virtual int get_type() { return wall; }
	~Wall() {};
};
