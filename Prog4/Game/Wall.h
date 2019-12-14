#pragma once
#include "Square.h"
class Wall : public Square {
public:
	Wall() {}; 
	//virtual bool go();
	virtual int get_type() { return wall; }
	//~Wall() {};
};
