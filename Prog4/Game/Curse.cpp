#include "Curse.h"
void Curse::damn(Enemy* enemy){
	enemy->set_HP(enemy->get_HP() - damage);
	if (enemy->get_type() == alive) { //продолжать действовать может только
		// на живого врага
		Alive_Enemy* alive = dynamic_cast<Alive_Enemy*>(enemy);
		alive->set_curse_damage(effect);
	}
}