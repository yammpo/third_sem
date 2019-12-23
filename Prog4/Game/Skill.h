#pragma once
#include <string>
enum type_of_skill { draining, curse, necromancy };
class Skill {
protected:
	std::string name;
	Skill* parent_skill;
	int mana_to_use;
public:
	Skill(std::string s = "name", Skill* sk = nullptr, int m = 0)
	{name = s; parent_skill = sk; mana_to_use = m;}
	virtual ~Skill() = 0 {}//��������� � ������ �����
	Skill& operator = (const Skill& sk) {
		name = sk.name;
		mana_to_use = sk.mana_to_use;
		parent_skill = sk.parent_skill;
		return *this;
	}
	Skill& operator = (Skill&& sk) {
		name = sk.name;
		mana_to_use = sk.mana_to_use;
		parent_skill = sk.parent_skill;
		delete[] sk.parent_skill;
		return *this;
	}
	Skill(const Skill& sk) {
		name = sk.name;
		mana_to_use = sk.mana_to_use;
		parent_skill = sk.parent_skill;
	}
	Skill(Skill&& sk) {
		name = sk.name;
		mana_to_use = sk.mana_to_use;
		parent_skill = sk.parent_skill;
		delete[] sk.parent_skill;
	}
	std::string get_name() { return name; }
	Skill* get_parent_skill() { return parent_skill; }
	int get_mana() { return mana_to_use; }
	void set_name(std::string s) { name = s;}
	void set_parent_skill(Skill* sk) { parent_skill = sk;}
	void set_mana(int m) { mana_to_use = m; }
	virtual int get_type() = 0;
};