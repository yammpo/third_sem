#include "Skill_Table.h"
Skill_Table::Skill_Table(int nn) {
	n = nn;
	skills.reserve(n);
	for (int i = 0; i < n; i++) {
		Skill *skill = new Draining();
		skills.push_back(skill);
	}
}
Skill_Table& Skill_Table::operator = (const Skill_Table& st) {
	n = st.n;
	skills.reserve(n);
	for (int i = 0; i < n; i++) {
		Skill *skill = st.skills[i];
		skills.push_back(skill);
	}
	return *this;
}
Skill_Table::Skill_Table(const Skill_Table& st) {
	n = st.n;
	skills.reserve(n);
	for (int i = 0; i < n; i++) {
		Skill *skill = st.skills[i];
		skills.push_back(skill);
	}
}
Skill_Table& Skill_Table::operator = (Skill_Table&& st) {
	n = st.n;
	skills = st.skills;
	for (int i = 0; i < st.n; i++) delete[] st.skills[i];
	st.skills.clear();
	return *this;
}
Skill_Table::Skill_Table(Skill_Table&& st) {
	n = st.n;
	skills = st.skills;
	for (int i = 0; i < st.n; i++) delete[] st.skills[i];
	st.skills.clear();
}
void Skill_Table::read_skills(std::string way1, std::string way2, std::string way3) {
	std::ifstream draining_file(way1);
	if (!draining_file.is_open()) throw std::runtime_error("File can't open!");
	std::ifstream necromancy_file(way2);
	//std::ifstream necromancy_file("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Necromancy.txt");
	if (!necromancy_file.is_open()) {
		//std::cout << "fuck";
		throw std::runtime_error("File can't open!");
	}
	std::ifstream curse_file(way3);
	if (!curse_file.is_open()) throw std::runtime_error("File can't open!");

	int number_of_necromancies, number_of_curses;
	necromancy_file >> number_of_necromancies;
	curse_file >> number_of_curses;
	n = number_of_necromancies + number_of_curses + 1;//1 for draining
	skills.reserve(n);
	int lvl;
	draining_file >> lvl;
	Skill *skill;
	skill = new Draining();
	Draining *draining = dynamic_cast<Draining*>(skill);
	draining->set_level(lvl);
	draining->set_name("draining");
	skills.push_back(skill);
	//название создаваемого вида нежити, мана тo use,
	//коэффициент, level to open, индекс родителя в таблице умений
	// если индекс родителя 0, то родителя нет, потому что 0 это иссушение
	while (!necromancy_file.eof()) {
		Skill *skill_1;
		skill_1 = new Necromancy();
		Necromancy *necromancy = dynamic_cast<Necromancy*>(skill_1);
		std::string name;
		necromancy_file >> name;
		necromancy->set_name(name);
		int mana;
		necromancy_file >> mana;
		necromancy->set_mana(mana);
		int k;
		necromancy_file >> k;
		necromancy->set_k(k);
		int lvl;
		necromancy_file >> lvl;
		necromancy->set_level_to_open(lvl);
		int index;
		necromancy_file >> index;
		if (index) necromancy->set_parent_skill(skills[index]);
		skills.push_back(skill_1);
	}
	while (!curse_file.eof()) {
		Skill *skill_2;
		skill_2 = new Curse();
		Curse *curse = dynamic_cast<Curse*>(skill_2);
		std::string name;
		curse_file >> name;
		curse->set_name(name);
		int mana;
		curse_file >> mana;
		curse->set_mana(mana);
		int dam;
		curse_file >> dam;
		curse->set_damage(dam);
		bool ef;
		curse_file >> ef;
		curse->set_effect(ef);
		int lvl;
		curse_file >> lvl;
		curse->set_level_to_open(lvl);
		int index;
		curse_file >> index;
		if (index) curse->set_parent_skill(skills[index + number_of_necromancies]);
		skills.push_back(skill_2);
	}
	draining_file.close();
	necromancy_file.close();
	curse_file.close();
}
void Skill_Table::show_skills() {
	for (int i = 0; i < skills.size(); i++) {
		std::cout << i;
		if (skills[i]->get_type() == draining) {
			std::cout << " name: " << skills[i]->get_name() << std::endl;
			std::cout << "mana to use:" << skills[i]->get_mana() << std::endl;
		}
		if (skills[i]->get_type() == necromancy) {
			std::cout << " name: " << skills[i]->get_name() << " creation " << std::endl;
			std::cout << "mana to use:" << skills[i]->get_mana();
			Skill *skill;
			skill = skills[i];
			Necromancy *necromancy = dynamic_cast<Necromancy*>(skill);
			std::cout << " k:" << necromancy->get_k();
			std::cout << " level to open:" << necromancy->get_level_to_open();
			if (skills[i]->get_parent_skill())
				std::cout << " parent skill: " << skills[i]->get_parent_skill()->get_name() << " creation ";
			std::cout << std::endl;
		}
		if (skills[i]->get_type() == curse) {
			std::cout << " name: " << skills[i]->get_name() << " curse " << std::endl;
			std::cout << "mana to use:" << skills[i]->get_mana();
			Skill *skill;
			skill = skills[i];
			Curse *curse = dynamic_cast<Curse*>(skill);
			std::cout << " damage:" << curse->get_damage();
			if (curse->get_effect()) std::cout << " ef: yes";
			else std::cout << " ef: no";
			//std::cout << " ef:" << curse->get_effect();
			std::cout << " level to open:" << curse->get_level_to_open();
			if (skills[i]->get_parent_skill())
				std::cout << " parent skill: " << skills[i]->get_parent_skill()->get_name();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}
