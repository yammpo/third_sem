#pragma once
#include "Enemy.h"
#include "Alive_Enemy.h"
class Elemental : public Enemy {
protected:
	Enemy* type;
public:
	Elemental(Enemy* tp = new Alive_Enemy()) : Enemy() { type = tp; }//очень сомневаюсь 
	Enemy* get_type_en() { return type; }
	void set_type(Enemy* en) {type = en;}
	Enemy* create_new_enemy(); // добавлять нового врага в массив врагов
	virtual int get_type() { return elemental; }
	//опять же, может лучше не здесь?
};