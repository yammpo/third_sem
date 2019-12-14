#pragma once
#include "Square.h"
class Floor : public Square {
public:
	Floor() {};
	//virtual bool go();
	virtual int get_type() { return flooor; }
	//~Floor(){}; // на всякий случай
};
