#include "Enemy.h"
Enemy::Enemy(int x_, int y_, int damage_, int hit_, int max_HP_,
	int HP_, int experience_, bool status_, std::string name_) {
	x = x_;
	y = y_;
	damage = damage_;
	hit = hit_;
	max_HP = max_HP_;
	HP = HP_;
	experience = experience_;
	status = status_;
	name = name_;
}
