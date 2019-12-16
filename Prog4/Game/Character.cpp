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
void Character::read_characteristics(std::string way) {
	std::ifstream characteristics(way);
	if (!characteristics.is_open()) throw std::runtime_error("File can't open!");
	while (!characteristics.eof()) {
		int x_;
		int y_;
		int max_mana_;
		int mana_;
		int max_HP_;
		int HP_;
		int experience_;
		int level_;
		int max_controlled_undead_;
		characteristics >> x_;
		x = x_;
		characteristics >> y_;
		y = y_;
		characteristics >> max_mana_;
		max_mana = max_mana_;
		characteristics >> mana_;
		mana = mana_;
		characteristics >> max_HP_;
		max_HP = max_HP_;
		characteristics >> HP_;
		HP = HP_;
		characteristics >> experience_;
		experience = experience_;
		characteristics >> level_;
		level = level_;
		characteristics >> max_controlled_undead_;
		max_controlled_undead = max_controlled_undead_;
	}
	characteristics.close();
}
void Character::read_skill_table(std::string way1, std::string way2, std::string way3) {
	skill_table.read_skills(way1, way2, way3);
}