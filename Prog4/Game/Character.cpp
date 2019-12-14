#include "Character.h"
//#include "Dungeon.h"
Character::Character(int x_, int y_, int max_mana_, int mana_, int max_HP_,
	int HP_, int experience_, int level_, int max_controlled_undead_) {
	x = x_;
	y = y_;
	max_mana = max_mana_;
	mana = mana_;
	max_HP = max_HP_;
	HP = HP_;
	experience = experience_;
	level = level_;
	max_controlled_undead = max_controlled_undead_;
	skill_table = Skill_Table();
}