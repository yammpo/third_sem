#include "Draining.h"
int Draining::get_essence(Alive_Enemy en) {
	// �� ��������� ����������� � use_skill
	int h = en.get_max_HP();
	return (h / 5 + level);
}