#pragma once
#include "Enemy.h"
//#include "Undead.h"
class Alive_Enemy : public Enemy {
private:
	int curse_damage;
	bool state;//false for dead, true for alive
public:
	Alive_Enemy(int cd = 2, bool st = true) : Enemy() { curse_damage = cd; state = st ; }
	int get_experience();//?
	int get_curse_damage() { return curse_damage ; }
	bool get_state() { return state; }
	void set_curse_damage(int cd) {curse_damage = cd; }
	void set_state(bool st) {state = st; }
	virtual int get_type() {
		if (state == false) return dead;
		else return alive;
	}
};