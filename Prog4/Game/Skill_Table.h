#pragma once
#include "Skill.h"
#include "Draining.h"
#include "Necromancy.h"
#include "Curse.h"
#include "Pseudovector.h"
#include <vector>
#include <fstream>
#include <iostream>
class Skill_Table {
private:
	std::vector<Skill*> skills;
	//Game::Vec<Skill*> skills;
	int n;
public:
	Skill_Table(int nn = 0);
	~Skill_Table() { 
	//for (int i = 0; i < skills.size(); i++) delete[] skills[i];
	//for (auto p : skills) delete p;
		skills.clear();
	}
	Skill_Table& operator = (const Skill_Table&);
	Skill_Table& operator = (Skill_Table&&);
	Skill_Table(const Skill_Table&);
	Skill_Table(Skill_Table&&);
	std::vector<Skill*> get_skills() { return skills; }
	//Game::Vec<Skill*> get_skills() { return skills; }
	Skill* get_skill(int i) { return skills[i]; }
	//int change_skill();
	int get_n() { return n; }
	void read_skills(std::string, std::string, std::string);
	// отдельные файлы для иссушения, некромантии и проклятия
	// int study_skill();// поиск по названию
	void show_skills();
};