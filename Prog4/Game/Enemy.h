#pragma once
#include <string>
//#include "Level.h"
enum type_of_enemy { dead, alive, elemental, undead, empty };
class Level;
class Enemy {
protected:
	std::string name;
	int max_HP;
	int HP;
	int damage;
	int hit;// ?
	int x;
	int y;
	int experience;// сколько опыта убитый враг приносит персонажу
	bool status;// true - агрессия, false - блуждает
public:
	Enemy(int x_ = 0, int y_ = 0, int damage_ = 10, int hit_ = 5, int max_HP_ = 10,
		int HP_ = 10, int experience_ = 1, bool status_ = false, std::string name_ = "enemy");
	int get_x() { return x; }
	int get_y() { return y; }
	void set_y(int yy) { y = yy; }
	void set_x(int xx) { x = xx; }
	std::string get_name() {return name ; }
	void set_name(std::string s) { name = s ; }
	int get_max_HP() { return max_HP ; }
	void set_max_HP(int mhp) { max_HP = mhp; }
	int get_damage() { return damage; }// возвращает сколько нанести урон , это число передается в персонажа
	void set_damage(int dm) { damage = dm ; }
	int get_hit();
	int change_hit(int);
	int get_HP() { return HP; }
	void set_HP(int hp) { HP = hp ; }
	int get_experience() { return experience; }
	void set_experience(int expr) { experience = expr; }
	void to_be_damaged(int); // принять урон от персонажа
	virtual int get_type() = 0;
	int go(int, int, Level); // передаются координаты персонажа и карта, возращает решение блуждать или идти
	//лучше в dungeon это сделать наверное
};