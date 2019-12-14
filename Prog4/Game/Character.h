#pragma once
#include "Skill_Table.h"
#include <string>
//enum go { step_ok, end_of_field, no_step_wall, no_step_closed_door, end_of_levels };
class Character {
private:
	int x;
	int y;
	int max_mana;
	int mana;
	int max_HP;
	int HP;
	int experience;
	int level;
	int max_controlled_undead;
	Skill_Table skill_table; 
public:
	Character(int x_ = 0, int y_ = 0, int max_mana_ = 10, int mana_ = 10, int max_HP_ = 10,
		int HP_ = 10, int experience_ = 0, int level_ = 0, int max_controlled_undead_ = 10);
	int get_x() { return x; }
	int get_y() { return y; }
	void set_y(int yy) { y = yy; }
	void set_x(int xx) { x = xx; }
	int get_max_mana() { return max_mana; }
	int get_mana() { return mana; }
	int get_max_HP() { return max_HP; }
	int get_HP() { return HP; }
	int get_experience() { return experience; }
	int get_level() { return level; }
	int get_max_controlled_undead() { return max_controlled_undead; }
	void set_max_mana(int mm) { max_mana = mm; }// �������
	void set_mana(int mm) { mana = mm; }
	void set_max_HP(int mh) { max_HP = mh; }
	void set_HP(int h) { HP = h; }
	void set_experience(int expr) { experience = expr; }
	void set_level(int lv) {level = lv; }
	void set_max_controlled_undead(int mcu) { max_controlled_undead = mcu; }
	void increase_experience(int e) { experience = experience + e; }
	void increase_level() {level++ ; } // if character.expirience == ������������� �����
	//character.increase_level() ?
	void to_be_damaged(int dam) { HP = HP - dam ; }// ������� ���� �� �����
	Skill_Table get_skill_table() { return skill_table; }
	void read_skill_table(std::string); // ��� �����
	void read_characteristics(std::string);// ��� �����
	void read_all(std::string);
	//int use_skill(char, int); // ��������� ����� ���� ������ �����
	//(�� ���� �� ������ �����) � ������, �� ���� ����� ������ ������ �� ������� ������ �����
	//����� ������� ������ ��� ���� ����� ������?

	//void check_step(int, int, int, Dungeon&, char); //���������� �����
	//void go(char, Dungeon&); // ��������� ����� ���� ������ �����, ��������� �����, ������
	// ������� �� ������ � ������ ����������� � ��� ��� �������� �� ������ �� �����
	// ���� ����� �� ����� �� ���������� ������ ��������� �� ������ ��������
	// ������ �������� �������� �����
	// ��� ���� � ���������? ����� �� ��������� dungeon �������� ���� ��� ������ � ������� ���������?
};