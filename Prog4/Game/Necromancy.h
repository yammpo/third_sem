#pragma once
#include "Skill.h"
class Necromancy : public Skill {
private:
	int k; // �����������
	int level_to_open; // �������, � �������� �������� ������ ���������� ������
public:
	Necromancy(int kk = 2, int lvl = 0) : Skill() { level_to_open = lvl; k = kk; }
	int get_k() { return k; }
	void set_k(int kk) { k = kk; }
	int get_level_to_open() { return level_to_open; }
	void set_level_to_open(int l) { level_to_open = l; }
	virtual int get_type() { return necromancy; }
};