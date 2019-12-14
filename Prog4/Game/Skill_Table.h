#pragma once
#include "Skill.h"
#include "Draining.h"
#include "Necromancy.h"
#include "Curse.h"
#include "Pseudovector.h"
#include <vector>
class Skill_Table {
private:
	std::vector<Skill*> skills;
	//Game::Vec<Skill*> skills;
	int n;
public:
	Skill_Table(int nn = 0);
	std::vector<Skill*> get_skills() { return skills; }
	Skill* get_skill(int i) { return skills[i]; }
	//int change_skill();
	int get_n() { return n; }
	int add_skill();// из файла чтобы считывать и добавлять
	// int study_skill();// поиск по названию
};