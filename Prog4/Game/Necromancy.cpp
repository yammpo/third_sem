#include "Necromancy.h"
Controlled_Undead* Necromancy::create_undead(Alive_Enemy en) { 
	// на мертвость проверяется в use_skill
	Controlled_Undead *contrund = new Controlled_Undead;
	contrund->set_max_HP(en.get_max_HP() / k);// c коэффициентами уже в файле посмотреть
	contrund->set_HP(en.get_max_HP() / k);
	contrund->set_damage(en.get_damage() / k);
	contrund->set_hit(en.get_hit() / k);
	contrund->set_x(en.get_x());
	contrund->set_y(en.get_y());
	contrund->set_name_of_alive(en.get_name());
	contrund->set_name(name);
	return contrund;
}