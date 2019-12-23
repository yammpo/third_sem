#pragma once
#include "Enemy.h"
#include "Alive_Enemy.h"
#include "Undead.h"
#include "Elemental.h"
#include "Controlled_Undead.h"
class Elemental : public Enemy {
protected:
	Enemy* type;
public:
	//Elemental(Enemy* tp = new Alive_Enemy()) : Enemy() { type = tp; }//очень сомневаюсь
	Elemental(Enemy* tp = nullptr) : Enemy() { type = tp; }
	virtual ~Elemental() {}
	// delete[] type всё портит. наверное это в другом месте удаляется
	Elemental& operator = (const Elemental&);
	Elemental& operator = (Elemental&& el) {
		type = el.type;
		delete[] el.type;
	}
	Elemental(const Elemental&);
	Elemental(Elemental&& el) {
		type = el.type;
		delete[] el.type;
	}
	Enemy* get_type_en() { return type; }
	void set_type(Enemy* en) {type = en;}
	Enemy* create_new_enemy(); // добавлять нового врага в массив врагов
	virtual int get_type() { return elemental; }
	//опять же, может лучше не здесь?
};