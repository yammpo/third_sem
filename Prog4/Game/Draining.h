#pragma once
#include "Skill.h"
#include "Alive_Enemy.h"
class Draining : public Skill {
private:
	int level;//уровень иссушения, от него (и от характеристик врага) завит получаемая эссенция
public:
	Draining(int lvl = 1) : Skill() { level = lvl; }
	int get_level() { return level; }
	void set_level(int lvl) { level = lvl; } // чтоб повышать тоже
	virtual int get_type() { return draining; }
	int get_essence(Alive_Enemy);
};