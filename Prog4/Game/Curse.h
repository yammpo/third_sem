#pragma once
#include "Skill.h"
#include <string>
#include "Enemy.h"
#include "Alive_Enemy.h"
class Curse : public Skill {
private:
	//std::string spell;
	int damage;
	bool effect; // 0 - false, 1 - true i guess))))
	int level_to_open; // уровень, с которого доступно данное конкретное умение
public:
	Curse( int dam = 5, bool e = false, int lvl = 0) : Skill() 
	{ level_to_open = lvl; damage = dam; effect = e; }
	~Curse() {};
	//std::string get_spell() {return spell; }
	//void set_spell(std::string s) { spell = s; }
	int get_damage() {return damage; }
	void set_damage(int dm) { damage = dm; }
	int get_level_to_open() { return level_to_open; }
	void set_level_to_open(int l) { level_to_open = l; }
	bool get_effect() { return effect; }
	void set_effect(bool e) { effect = e; }
	virtual int get_type() { return curse; }
	void damn(Enemy*);
};