#pragma once
#include "Square.h"
#include "Floor.h"
#include "Stairs.h"
#include "Door.h"
#include "Wall.h"
#include "Enemy.h"
#include "Alive_Enemy.h"
#include "Undead.h"
#include "Elemental.h"
#include "Controlled_Undead.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Level {
private:
	std::vector<std::vector<Square*>> squares;
	std::vector<Enemy*> enemies;
	int h; // ������
	int w; // ������
	// ���-�� enemies �� ��������, �� �������� �� sizeof ������� enimies
	// � �������� ������ � ������ ����� ����� ���� �� �������
public:
	Level(int hh = 0, int ww = 0, int enms = 0);// ������, ������ � ���������� ������
	int get_h() { return h; }
	int get_w() { return w; }
	void set_h(int hh) { h = hh; }
	void set_w(int ww) { w = ww; }
	Square* get_square(int i, int j) { return squares[i][j]; }
	std::vector<std::vector<Square*>>  get_squares() { return squares; }
	std::vector<Enemy*> get_enemies() { return enemies; }
	void set_enemies(std::vector<Enemy*> en) { enemies = en; }
	void set_enemy(Enemy *en, int i) { enemies[i] = en; }
	//Enemy* get_enemy(int i) { return enemies[i]; }
	void read_squares(std::string); // ����������� squares �� ����� ������� ������
	void read_enemies(std::string); // ������������� �����
	void show_enemies();
	void show_controlled_undead();
};