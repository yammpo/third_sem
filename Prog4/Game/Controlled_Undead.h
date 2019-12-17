#pragma once
#include "Undead.h"
enum order { move, stand, attack };
class Controlled_Undead : public Undead {
private:
	int order;// двигаться стоять атаковать
public:
	Controlled_Undead(int ord = stand) : Undead() { order = ord; }
	~Controlled_Undead() {};
	int get_order() { return order; }
	void set_order(int ord) { order = ord;}
	virtual int get_type() { return controlled_undead; }
	virtual int get_type_undead() { return controlled; }
};