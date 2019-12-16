#include "Draining.h"
int Draining::get_essence(Alive_Enemy en) {
	// на мертвость проверяется в use_skill
	int h = en.get_max_HP();
	return (h / 5 + level);
}