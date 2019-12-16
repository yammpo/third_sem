#pragma once
#include "Enemy.h"
enum type_of_undead { controlled, not_controlled };
class Undead : public Enemy {
protected:
	std::string name_of_alive;
public:
	Undead(std::string name = "default") : Enemy() { name_of_alive = name; }
	std::string get_name_of_alive() { return name_of_alive; }
	void set_name_of_alive(std::string name) { name_of_alive = name; }
	virtual int get_type() { return undead; }
	virtual int get_type_undead() { return not_controlled; }
};