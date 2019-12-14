#include "Skill_Table.h"
Skill_Table::Skill_Table(int nn) {
	n = nn;
	skills.reserve(n);
	for (int i = 0; i < n; i++) {
		Skill *skill = new Draining();
		skills.push_back(skill);
	}
}