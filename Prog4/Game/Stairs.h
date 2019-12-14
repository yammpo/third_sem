#pragma once
#include "Square.h"
enum updown { up, down };
class Stairs : public Square {
private:
	bool updown;
public:
	Stairs(bool ud = 0) : updown(ud) {};
	virtual int get_type();
	bool get_updown() { return updown; }
	void set_updown(bool ud) { updown = ud; }
	//virtual bool go();
	//~Stairs() {};
};
