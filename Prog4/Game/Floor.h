#pragma once
#include "Square.h"
class Floor : public Square {
private:
	bool state; //for win
public:
	Floor(bool st = 0) : state(st) {};
	//virtual bool go();
	void set_state(bool s) { state = s; }
	virtual int get_type() { 
		if (state == 0) return flooor;
		else return winner;
	}
	//~Floor(){}; // на всякий случай
};
