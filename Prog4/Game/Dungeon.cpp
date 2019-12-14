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
	if ((i < 0) || (i > levels[k].get_h())) return end_of_field;
	if ((j < 0) || (j > levels[k].get_w())) return end_of_field;
	int type = levels[k].get_square(i, j)->get_type();
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
			if ((i + 1 >= 0) && (i + 1 <= levels[k].get_h())) character.set_y(i+1);
			else return end_of_field;
			if ((j >= 0) && (j <= levels[k].get_w())) character.set_x(j);
			else return end_of_field;
		}
		if (c == 'w') {
			if ((i - 1 >= 0) && (i - 1 <= levels[k].get_h())) character.set_y(i-1);
			else return end_of_field;
			if ((j >= 0) && (j <= levels[k].get_w())) character.set_x(j);
			else return end_of_field;
		}
		if (c == 'a') {
			if ((i >= 0) && (i <= levels[k].get_h())) character.set_y(i);
			else return end_of_field;
			if ((j - 1 >= 0) && (j - 1 <= levels[k].get_w())) character.set_x(j-1);
			else return end_of_field;
		}
		if (c == 'd') {
			if ((i >= 0) && (i <= levels[k].get_h())) character.set_y(i);
			else return end_of_field;
			if ((j + 1 >= 0) && (j + 1 <= levels[k].get_w())) character.set_x(j+1);
			else return end_of_field;
		}
	}
	// сделать клетку под лестницей недоступной для врага
	if (type == stairs_down) {
		if (level_number < n) level_number++; // и указатель на след уровень или 
		// это уже в dungeon обращаться? да
		else return end_of_field;
	}
	if (type == stairs_up) {
		if (level_number > 0) level_number--;
		else return end_of_field;
	}
	// еще проверить нет ли на этой клетке врага!
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
		if ((levels[k].get_enemies()[ch]->get_x() == i) &&
			(levels[k].get_enemies()[ch]->get_y() == j)) {
			type = levels[k].get_enemies()[ch]->get_type();
			break;
		}
		//убедились что в этой клетке есть враг и сохранили его тип
	} 
	if (type == empty) return no_enemy;
	if (character.get_skill_table().get_skills()[index]->get_type() == draining) {
		// пока что превращает только в здоровье
		if (type == dead) {
			Skill* skill = character.get_skill_table().get_skills()[index];
			Draining* draining = dynamic_cast<Draining*>(skill);
			Enemy *enemy = levels[k].get_enemies()[ch];
			Alive_Enemy *al_en = dynamic_cast<Alive_Enemy*>(enemy);
			int ess = draining->get_essence(*al_en);// не уверена во всех этих приведениях
			character.set_HP(character.get_HP() + ess);// если hp превысит max hp что делать?
			levels[k].get_enemies().erase(levels[k].get_enemies().begin() + ch); 
			//удалили использованный труп
			return used_ok;
		}
		else return cant_be_used_to_this_enemy;
	}
	if (character.get_skill_table().get_skills()[index]->get_type() == necromancy) {
		// отдавать нежити приказы?
		// проверять уровень с которого доступно умение и есть ли у него родительское
		if (type == dead) {
			Skill* skill = character.get_skill_table().get_skills()[index];
			Necromancy* draining = dynamic_cast<Necromancy*>(skill);
		}
	}
}
int Dungeon::character_use_skill(char c, int index) {//сначала вводится с, потом index
	if (c == 'w') return check_enemy(level_number, character.get_y() + 1, character.get_x(), index);
	if (c == 's') return check_enemy(level_number, character.get_y() - 1, character.get_x(), index);
	if (c == 'a') return check_enemy(level_number, character.get_y(), character.get_x() - 1, index);
	if (c == 'd') return check_enemy(level_number, character.get_y(), character.get_x() + 1, index);
}
void Dungeon::read_character() {
	std::ifstream characteristics("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Character.txt");
	if (!characteristics.is_open()) throw std::runtime_error("File can't open!");
	while (!characteristics.eof()) {
		int x_;
		int y_;
		int max_mana_;
		int mana_;
		int max_HP_;
		int HP_;
		int experience_;
		int level_;
		int max_controlled_undead_;
		characteristics >> x_;
		character.set_x(x_);
		characteristics >> y_;
		character.set_y(y_);
		characteristics >> max_mana_;
		character.set_max_mana(max_mana_);
		characteristics >> mana_;
		character.set_mana(mana_);
		characteristics >> max_HP_;
		character.set_max_HP(max_HP_);
		characteristics >> HP_;
		character.set_HP(HP_);
		characteristics >> experience_;
		character.set_experience(experience_);
		characteristics >> level_;
		character.set_level(level_);
		characteristics >> max_controlled_undead_;
		character.set_max_controlled_undead(max_controlled_undead_);
		characteristics.close();// еще сохранять изменения надо, но не здесь
		// ещё считать умения
	}
}

void Dungeon::read_levels() {
	levels[0].read_squares("D:\\MASHA\\!!!!МИФИ\\лабы инфа\\третий семестр\\Prog4\\Game\\Level_1_Squares.txt");
}
void Dungeon::show(int i) {
	Level lev = levels[i];
	std::vector<std::vector<Square*>> squares = lev.get_squares();
	int h = lev.get_h();
	int w = lev.get_w();
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int type = squares[i][j]->get_type();
			if ((character.get_x() == j) && (character.get_y() == i)) std::cout << "u ";
			else {
			if (type == flooor) std::cout << ". ";
			if (type == wall) std::cout << "# ";
			if (type == stairs_down) std::cout << "> ";
			if (type == stairs_up) std::cout << "< ";
			if (type == opened_door) std::cout << "/ ";
			if (type == closed_door) std::cout << "+ ";
			}
		}
		std::cout << std::endl;
	}
}