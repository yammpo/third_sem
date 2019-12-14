#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Character.h"
#include "Level.h"
enum go { step_ok, end_of_field, no_step_wall, no_step_closed_door, end_of_levels };
enum use_skills { used_ok, no_enemy, cant_be_used_to_this_enemy};
// w - �����, a - �����, s - ����, d - ������ 
//������������� ������� ������ ������?..
class Dungeon {
private:
	Character character;
	std::vector<Level> levels;
	int level_number; // ������� �������
	int n; // ���������� �������
public:
	Dungeon(int nn = 0);
	Character get_character() { return character; }
	int get_level_number() { return level_number; }
	int get_n() { return n; }
	Level get_level(int i) { return levels[i]; }
	void set_level_number(int ln) { level_number = ln; }
	void read_all(); // �������� read_levels & read_character
	void read_levels();
	void read_character();
	void go_enemies();// �������� go ��� ���� ������
	int check_step(int, int, int, char);
	int go_character(char);
	int check_enemy(int, int, int, int);
	int character_use_skill(char, int); //��������� ����� ���� ������ �����
	//(�� ���� �� ������ �����) � ������, �� ���� ����� ������ ������ �� ������� ������ �����
	void show(int i); //������� ����� ��� ����������� ����, ���� ����� � �����
	//std::vector<std::vector<char>> show(int i); // ���������� ����� ������ �� ������ ������
	// ����� ������� ���� ��������� ����� i guess
};
