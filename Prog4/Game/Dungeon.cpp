#include "Dungeon.h"
Dungeon::Dungeon(int nn) {
	level_number = 0;
	n = nn;
	character = Character();//new?
	levels.reserve(n);
	for (int i = 0; i < n; i++) {
		Level level = Level();
		levels.push_back(level);
	}
}
int Dungeon::check_step(int k, int j, int i, char c) { // i for y, j for x
	if ((i < 0) || (i > levels[k].get_h() - 1)) return end_of_field;
	if ((j < 0) || (j > levels[k].get_w() - 1)) return end_of_field;
	std::vector<Enemy*> enemies = levels[k].get_enemies();
	for (int tmp = 0; tmp < enemies.size(); tmp++) {
		// не очень хорошо, что каждый раз по всему массиву врагов проходимся
		// надо как-то исключать тех, по которым уже прошлись
		if ((enemies[tmp]->get_x() == j) && (enemies[tmp]->get_y() == i))
			return emeny;
	}
	int type = levels[k].get_square(i, j)->get_type();
	if (type == winner) {
		character.set_y(i);
		character.set_x(j);
		return win;
	}
	if (type == flooor) {
		character.set_y(i);
		character.set_x(j);
		//if ((i >= 0) && (i <= levels[k].get_h())) character.set_y(i);
		//else return end_of_field;
		//if ((j >= 0) && (j <= levels[k].get_w())) character.set_x(j);
		//else return end_of_field;
	}
	if (type == wall) return no_step_wall;
	if (type == closed_door) return no_step_closed_door;
	if (type == opened_door) {
		if (c == 's') {
			if ((i + 1 < 0) || (i + 1 > levels[k].get_h() - 1)) return end_of_field;
			if ((j < 0) || (j > levels[k].get_w() - 1)) return end_of_field;
			for (int tmp = 0; tmp < enemies.size(); tmp++) {
				// не очень хорошо, что каждый раз по всему массиву врагов проходимся
				// надо как-то исключать тех, по которым уже прошлись
				if ((enemies[tmp]->get_x() == j) && (enemies[tmp]->get_y() == i + 1))
					return emeny;
			}
			 character.set_y(i+1); 
			 character.set_x(j);
		}
		if (c == 'w') {
			if ((i - 1 < 0) || (i - 1 > levels[k].get_h() - 1)) return end_of_field;
			if ((j < 0) || (j > levels[k].get_w() - 1)) return end_of_field;
			for (int tmp = 0; tmp < enemies.size(); tmp++) {
				// не очень хорошо, что каждый раз по всему массиву врагов проходимся
				// надо как-то исключать тех, по которым уже прошлись
				if ((enemies[tmp]->get_x() == j) && (enemies[tmp]->get_y() == i - 1))
					return emeny;
			}
			character.set_y(i-1);
			character.set_x(j);
		}
		if (c == 'a') {
			if ((i < 0) || (i > levels[k].get_h() - 1)) return end_of_field;
			if ((j - 1 < 0) || (j - 1 > levels[k].get_w() - 1)) return end_of_field;
			for (int tmp = 0; tmp < enemies.size(); tmp++) {
				// не очень хорошо, что каждый раз по всему массиву врагов проходимся
				// надо как-то исключать тех, по которым уже прошлись
				if ((enemies[tmp]->get_x() == j - 1) && (enemies[tmp]->get_y() == i))
					return emeny;
			}
			character.set_y(i);
			character.set_x(j-1);
		}
		if (c == 'd') {
			if ((i < 0) || (i > levels[k].get_h() - 1)) return end_of_field;
			if ((j + 1 < 0) || (j + 1 > levels[k].get_w() - 1)) return end_of_field;
			for (int tmp = 0; tmp < enemies.size(); tmp++) {
				// не очень хорошо, что каждый раз по всему массиву врагов проходимся
				// надо как-то исключать тех, по которым уже прошлись
				if ((enemies[tmp]->get_x() == j + 1) && (enemies[tmp]->get_y() == i))
					return emeny;
			}
			character.set_y(i);
			character.set_x(j+1);
		}
	}	// сделать клетку под лестницей недоступной для врага
	// на последнем уровне не должно быть лестницы вниз, на первом лестницы наверх
	// на последнем уровне сделать типа кристалик и если на него встал то победил
	if (type == stairs_down) {
		if (level_number < n) {
			level_number++;
			character.set_y(i);
			character.set_x(j);
		}
		else return end_of_levels;
	}
	if (type == stairs_up) {
		if (level_number > 0) {
			level_number--;
			character.set_y(i);
			character.set_x(j);
		}
		else return end_of_levels;
	}
	return step_ok;
};
int Dungeon::go_character(char c) {
	if (c == 'w') return check_step(level_number, character.get_x(), character.get_y() - 1, 'w');
	if (c == 's') return check_step(level_number, character.get_x(), character.get_y() + 1, 's');
	if (c == 'a') return check_step(level_number, character.get_x() - 1, character.get_y(), 'a');
	if (c == 'd') return check_step(level_number, character.get_x() + 1, character.get_y(), 'd');
}
int Dungeon::check_enemy(int k, int i, int j, int index) {
	int type = empty;
	unsigned ch;
	for (ch = 0; ch < levels[k].get_enemies().size(); ch++) {
		if ((levels[k].get_enemies()[ch]->get_y() == i) &&
			(levels[k].get_enemies()[ch]->get_x() == j)) {
			type = levels[k].get_enemies()[ch]->get_type();
			break;
		}
		//убедились что в этой клетке есть враг и сохранили его тип
	} 
	if (type == empty) return no_enemy;
	if (character.get_skill_table().get_skills()[index]->get_type() == draining) {
		// пока что превращает только в здоровье, но надо сделать опцию выбора
		if (type == dead) {
			std::cout << "u want to increase mana (m) or hp (h)?" << std::endl;
			char g;
			std::cin >> g;
			Skill* skill = character.get_skill_table().get_skills()[index];
			Draining* draining = dynamic_cast<Draining*>(skill);
			Enemy *enemy = levels[k].get_enemies()[ch];
			Alive_Enemy *al_en = dynamic_cast<Alive_Enemy*>(enemy);
			int ess = draining->get_essence(*al_en);
			if (g == 'h') {
				if (character.get_HP() == character.get_max_HP()) return max_HP;
				else character.set_HP(character.get_HP() + ess);
			}
			else {
				if (character.get_mana() == character.get_max_mana()) return maxmana;
				else character.set_mana(character.get_mana() + ess);
			}
			std::vector<Enemy*> enemies = levels[k].get_enemies();
			enemies.erase(enemies.begin() + ch); 
			levels[k].set_enemies(enemies);
			//std::cout << enemies.size();
			//удалили использованный труп
			return used_ok;
		}
		else return cant_be_used_to_this_enemy;
	}
	if (character.get_skill_table().get_skills()[index]->get_type() == necromancy) {
		// controlled undead запихивать в вектор врагов на место трупа!!! просто поменять элемент
		// в выводе характеристик врагов не выводить нашу нежить, сделать отдельный пункт в меню
		// чтоб выводились характеристики нашей нежити
		if (type == dead) {
			Skill* skill = character.get_skill_table().get_skills()[index];
			Necromancy* necromancy = dynamic_cast<Necromancy*>(skill);
			std::vector<Enemy*> enemies = levels[k].get_enemies();
			Enemy *enemy = enemies[ch];
			Alive_Enemy *al_en = dynamic_cast<Alive_Enemy*>(enemy);
			if (character.get_level() < necromancy->get_level_to_open()) return level;
			if (character.get_mana() < necromancy->get_mana()) return mana;
			// CHECK PARENT SKILL
			// CHECK MAX UNDEAD CONTROLLED
			// SET ORDER
			character.set_mana(character.get_mana() - necromancy->get_mana());
			enemies[ch] = necromancy->create_undead(*al_en);
			levels[k].set_enemy(enemies[ch], ch);
			return used_ok;
		}
		else return cant_be_used_to_this_enemy;
	}
	if (character.get_skill_table().get_skills()[index]->get_type() == curse) {
		if ((type == dead) || (type == controlled_undead)) return cant_be_used_to_this_enemy;
		Skill* skill = character.get_skill_table().get_skills()[index];
		Curse* curse = dynamic_cast<Curse*>(skill);
		if (character.get_level() < curse->get_level_to_open()) return level;
		if (character.get_mana() < curse->get_mana()) return mana;
		character.set_mana(character.get_mana() - curse->get_mana());
		std::vector<Enemy*> enemies = levels[k].get_enemies();
		Enemy *enemy = enemies[ch];
		curse->damn(enemy);
		if (enemy->get_HP() <= 0) {
			enemies.erase(enemies.begin() + ch);
			levels[k].set_enemies(enemies);
			character.set_experience(enemy->get_experience());
		}
		else levels[k].set_enemy(enemy, ch);
		return used_ok;
	}
}
int Dungeon::use_skill(char c, int index) {//сначала вводится с, потом index
	if (c == 'w') return check_enemy(level_number, character.get_y() - 1, character.get_x(), index);
	if (c == 's') return check_enemy(level_number, character.get_y() + 1, character.get_x(), index);
	if (c == 'a') return check_enemy(level_number, character.get_y(), character.get_x() - 1, index);
	if (c == 'd') return check_enemy(level_number, character.get_y(), character.get_x() + 1, index);
}
void Dungeon::read_character() {
	character.read_characteristics("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Character.txt");
	  // еще сохранять изменения надо, но не здесь
	character.read_skill_table
		("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Draining.txt",
		"D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Necromancy.txt",
		"D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Curse.txt");
}
void Dungeon::save_character() {
	character.save_characteristics("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Character_Saved.txt");
}
void Dungeon::read_saved_character() {
	character.read_characteristics("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Character_Saved.txt");
}

void Dungeon::read_levels() {
	/*std::ifstream dimension("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\info_levels.txt");
	// первая цифра - количество уровней, вторая - текущий уровень
	if (!dimension.is_open()) throw std::runtime_error("File can't open!");
	int number_of_levels, lev_now;
	dimension >> number_of_levels >> lev_now;
	level_number = lev_now;
	n = number_of_levels;
	levels.reserve(n);
	for (int i = 0; i < n; i++) {
		Level level = Level();
		levels.push_back(level);
	} */
	levels[0].read_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_1_Squares.txt");
	levels[0].read_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_1_Enemies.txt");
	levels[1].read_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_2_Squares.txt");
	levels[1].read_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_2_Enemies.txt");
	levels[2].read_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_3_Squares.txt");
	levels[2].read_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_3_Enemies.txt");
}
void Dungeon::read_saved_levels() {
	levels[0].read_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_1_Squares_Saved.txt");
	levels[0].read_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_1_Enemies_Saved.txt");
	levels[1].read_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_2_Squares_Saved.txt");
	levels[1].read_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_2_Enemies_Saved.txt");
	levels[2].read_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_3_Squares_Saved.txt");
	levels[2].read_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_3_Enemies_Saved.txt");
}
void Dungeon::save_levels() {
	levels[0].save_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_1_Squares_Saved.txt");
	levels[0].save_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_1_Enemies_Saved.txt");
	levels[1].save_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_2_Squares_Saved.txt");
	levels[1].save_enemies("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_2_Enemies_Saved.txt");
	levels[2].save_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_3_Squares_Saved.txt");
	levels[2].save_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_3_Enemies_Saved.txt");
}
void Dungeon::show_level(int i) {//текущий, не в level так как нужны координаты персонажа
	Level lev = levels[i];
	// расставить врагов!
	// b - труп, a - живой, d - элементаль, c - нежить, 1 - твой
	std::vector<std::vector<Square*>> squares = lev.get_squares();
	std::vector<Enemy*> enemies = lev.get_enemies();
	int h = lev.get_h();
	int w = lev.get_w();
	bool flag = true;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			flag = true;
			int type = squares[i][j]->get_type();
			if ((character.get_x() == j) && (character.get_y() == i)) {
				std::cout << "u ";
				flag = false;
			}
			for (int tmp = 0; tmp < enemies.size(); tmp++) {
				// не очень хорошо, что каждый раз по всему массиву врагов проходимся
				// надо как-то исключать тех, по которым уже прошлись
				if ((enemies[tmp]->get_x() == j) && (enemies[tmp]->get_y() == i)) {
					if (enemies[tmp]->get_type() == alive) std::cout << "a ";
					if (enemies[tmp]->get_type() == dead) std::cout << "b ";
					if (enemies[tmp]->get_type() == controlled_undead) std::cout << "1 ";
					if (enemies[tmp]->get_type() == undead) std::cout << "c ";
					if (enemies[tmp]->get_type() == elemental) std::cout << "d ";
					flag = false;
				}
			}
			if (flag) {
				if (type == flooor) std::cout << ". ";
				if (type == wall) std::cout << "# ";
				if (type == stairs_down) std::cout << "> ";
				if (type == stairs_up) std::cout << "< ";
				if (type == opened_door) std::cout << "/ ";
				if (type == closed_door) std::cout << "+ ";
				if (type == winner) std::cout << "$ ";
			}
		}
		std::cout << std::endl;
	}
}
void Dungeon::show_characteristics() {
	std::cout << "your characteristics right now: " << std::endl;
	std::cout << "max mana: " << character.get_max_mana();
	std::cout << " mana: " << character.get_mana();
	std::cout << " max HP: " << character.get_max_HP();
	std::cout << " HP: " << character.get_HP() << std::endl;
	std::cout << "experience: " << character.get_experience();
	std::cout << " level: " << character.get_level();
	std::cout << " max controlled undead: " << character.get_max_controlled_undead() << std::endl << std::endl;
}
void Dungeon::show_skill_table() {
	character.get_skill_table().show_skills();
}
void Dungeon::show_enemies() {
	levels[level_number].show_enemies();
}
void Dungeon::show_controlled_undead() {
	levels[level_number].show_controlled_undead();
}
int Dungeon::check_door(int x, int y, bool fl) {
	if ((y >= 0) && (y <= levels[level_number].get_h()) &&
		(x >= 0) && (x <= levels[level_number].get_w())) {
		Square *square = levels[level_number].get_square(y, x);
		if ((square->get_type() == closed_door) && (fl == open)) {
			Door *door = dynamic_cast<Door*>(square);
			door->open();// изменить в самой двери
			return all_ok;
		}
		else if ((square->get_type() == opened_door) && (fl == close)) {
			Door *door = dynamic_cast<Door*>(square);
			door->close();
			return all_ok;
		}
		else if ((square->get_type() == opened_door) && (fl == open)) return already_opened; 
		else if ((square->get_type() == closed_door) && (fl == close)) return already_closed;
		else return no_door;
	}	
	else return no_door;
}
int Dungeon::change_door(char c, bool fl) {
	int x = character.get_x(), y = character.get_y();
	if (c == 'w') return check_door(x, y - 1, fl);
	if (c == 's') return check_door(x, y + 1, fl);
	if (c == 'a') return check_door(x - 1, y, fl);
	if (c == 'd') return check_door(x + 1, y, fl);
}