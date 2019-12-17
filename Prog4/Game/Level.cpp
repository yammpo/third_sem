#include "Level.h"
Level::Level(int hh, int ww, int enms) {
	h = hh;
	w = ww;
	squares.reserve(h);
	for (int i = 0; i < h; i++) {
		std::vector<Square*> vec;
		vec.reserve(w);
		for (int j = 0; j < w; j++) {
			Square *square = new Floor(); // не уверена
			//Floor *floor = dynamic_cast<Floor*>(square); 
			// это только чтоб методы потом юзать. см. википедию. в конструкторе думаю не надо
			vec.push_back(square);
			//squares[i][j]->get_type();
		}
		squares.push_back(vec);
	}
	enemies.reserve(enms);
	for (int i = 0; i < enms; i++) {
		Enemy *enemy = new Alive_Enemy();
		//Alive_Enemy *alive_enemy = static_cast<Alive_Enemy*>(enemy); //??????!??!?!
		enemies.push_back(enemy);
	}
}
Level::~Level() {
	enemies.clear();
	for (int i = 0; i < squares.size(); i++) squares[i].clear();
	squares.clear();
}
void Level::read_squares(std::string way) {
	std::ifstream lev(way);
	if (!lev.is_open()) throw std::runtime_error("File can't open!");
	for (int j = 0; j < w; j++)
		if (!squares[j].empty()) squares[j].clear();
	if (!squares.empty()) squares.clear();
	int hh, ww;
	lev >> hh;
	h = hh;
	lev >> ww;
	w = ww;
	//std::cout << w;
	while (!lev.eof()) {
		squares.reserve(h);
		for (int i = 0; i < h; i++) {
			std::vector<Square*> vec;
			vec.reserve(w);
			for (int j = 0; j < w; j++) {
				char c;
				lev >> c;
				Square *square;
				if (c == '.') square = new Floor(); 
				if (c == '$') {
					square = new Floor();
					Floor *floor = dynamic_cast<Floor*>(square);
					floor->set_state(1);
				}
				if (c == '#') square = new Wall();
				if (c == '>') {
					square = new Stairs();
					Stairs *stairs = dynamic_cast<Stairs*>(square); 
					stairs->set_updown(down);
				}
				if (c == '<') {
					square = new Stairs();
					Stairs *stairs = dynamic_cast<Stairs*>(square);
					stairs->set_updown(up);
				}
				if (c == '/') square = new Door();
				if (c == '+') {
					square = new Door();
					Door *door = dynamic_cast<Door*>(square);
					door->set_status(closed);
				}
				vec.push_back(square);
			}
			squares.push_back(vec);
		}
	}
	lev.close();
}
void Level::save_squares(std::string way) {
	std::ofstream lev(way);
	lev << h << std::endl;
	lev << w << std::endl;
	squares.reserve(h);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int type = squares[i][j]->get_type();
			if (type == flooor) lev << ". ";
			if (type == wall) lev << "# ";
			if (type == stairs_down) lev << "> ";
			if (type == stairs_up) lev << "< ";
			if (type == opened_door) lev << "/ ";
			if (type == closed_door) lev << "+ ";
			if (type == winner) lev << "$ ";
		}
		lev << std::endl;
	}
	lev.close();
}
void Level::read_enemies(std::string way) {
	std::ifstream enem(way);
	if (!enem.is_open()) throw std::runtime_error("File can't open!");
	int number_of_enemies;
	enem >> number_of_enemies;
	if (!enemies.empty()) enemies.clear();
	enemies.reserve(number_of_enemies);
	//тип врага(живой, нежить, элементаль, супер нежить), 
	//имя, max HP, HP, damage, hit, x, y, expirience, status
	while (!enem.eof()) {
		Enemy *enemy;
		std::string type, name;
		enem >> type >> name;
		int max_hp, hp, damage, hit, x, y, experience;
		enem >> max_hp >> hp >> damage >> hit >> x >> y >> experience;
		bool status; enem >> status; 
		if (type == "alive") { 
			enemy = new Alive_Enemy();
			Alive_Enemy *alive_enemy = dynamic_cast<Alive_Enemy*>(enemy);
			int curse_damage;
			bool state;
			enem >> curse_damage >> state;
			enemy->set_name(name); //сделать сеттеры не войд мб
			enemy->set_max_HP(max_hp);
			enemy->set_HP(hp);
			enemy->set_damage(damage);
			enemy->set_hit(hit);
			enemy->set_x(x);
			enemy->set_y(y);
			enemy->set_experience(experience);
			enemy->set_status(status);
			alive_enemy->set_curse_damage(curse_damage);
			alive_enemy->set_state(state);
		}
		if (type == "undead") { 
			enemy = new Undead();
			Undead *undead = dynamic_cast<Undead*>(enemy);
			std::string name_alive;
			enem >> name_alive;
			enemy->set_name(name); //сделать сеттеры не войд мб
			enemy->set_max_HP(max_hp);
			enemy->set_HP(hp);
			enemy->set_damage(damage);
			enemy->set_hit(hit);
			enemy->set_x(x);
			enemy->set_y(y);
			enemy->set_experience(experience);
			enemy->set_status(status);
			undead->set_name_of_alive(name_alive);
		}
		if (type == "controlled") {
			enemy = new Controlled_Undead();
			Controlled_Undead *controlled = dynamic_cast<Controlled_Undead*>(enemy);
			std::string name_alive;
			int order;
			enem >> name_alive;
			enem >> order;
			enemy->set_name(name); //сделать сеттеры не войд мб
			enemy->set_max_HP(max_hp);
			enemy->set_HP(hp);
			enemy->set_damage(damage);
			enemy->set_hit(hit);
			enemy->set_x(x);
			enemy->set_y(y);
			enemy->set_experience(experience);
			enemy->set_status(status);
			controlled->set_name_of_alive(name_alive);
			controlled->set_order(order);
		}
		if (type == "elemental") { 
			enemy = new Elemental();
			Elemental *elemental = dynamic_cast<Elemental*>(enemy);
			// в файле индекс типа создаваемого противника
			int index;
			enem >> index;
			enemy->set_name(name); //сделать сеттеры не войд мб
			enemy->set_max_HP(max_hp);
			enemy->set_HP(hp);
			enemy->set_damage(damage);
			enemy->set_hit(hit);
			enemy->set_x(x);
			enemy->set_y(y);
			enemy->set_experience(experience);
			enemy->set_status(status);
			elemental->set_type(enemies[index]);
		}
		enemies.push_back(enemy);
	}
	enem.close();
}
void Level::save_enemies(std::string way) {
	std::ofstream enem(way);
	enem << enemies.size() << std::endl;
	for (int i = 0; i < enemies.size(); i++) {
		if ((enemies[i]->get_type() == alive) || (enemies[i]->get_type() == dead))
			enem << "alive ";
		if (enemies[i]->get_type() == undead) enem << "undead ";
		if (enemies[i]->get_type() == controlled_undead) enem << "controlled ";
		if (enemies[i]->get_type() == elemental) enem << "elemental ";
		enem << enemies[i]->get_name() << " "
			<< enemies[i]->get_max_HP() << " " << enemies[i]->get_HP() << " "
			<< enemies[i]->get_damage() << " " << enemies[i]->get_hit() << " "
			<< enemies[i]->get_x() << " " << enemies[i]->get_y() << " "
			<< enemies[i]->get_experience() << " " << enemies[i]->get_status() << " ";
		if ((enemies[i]->get_type() == alive) || (enemies[i]->get_type() == dead)) {
			Alive_Enemy *alive_enemy = dynamic_cast<Alive_Enemy*>(enemies[i]);
			enem << alive_enemy->get_curse_damage() << " " << alive_enemy->get_state();
		}
		if (enemies[i]->get_type() == elemental) {
			Elemental *elemental = dynamic_cast<Elemental*>(enemies[i]);
			Enemy *enemy = elemental->get_type_en();
			// узнать индекс по указателю
			for (int j = 0; j < enemies.size(); j++) {
				if (enemies[j] == enemy) enem << j;
			} // если нет надо тоже че-то записать типа -1 или как-то обозначить что он больше никого не создает
		}
		if (enemies[i]->get_type() == undead) {
			Undead *undead = dynamic_cast<Undead*>(enemies[i]);
			enem << undead->get_name_of_alive();
		}
		if (enemies[i]->get_type() == controlled_undead) {
			Controlled_Undead *controlled = dynamic_cast<Controlled_Undead*>(enemies[i]);
			enem << controlled->get_name_of_alive() << " " << controlled->get_order();
		}
		enem << std::endl;
	}
}
void Level::show_enemies() {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->get_type() != controlled_undead) {
			//std::cout << i << " " << enemies[i]->get_x() << " " << enemies[i]->get_y();
			std::cout << "type: ";
			//Enemy *enemy = enemies[i];
			//dynamic cast
			if ((enemies[i]->get_type() == dead) || (enemies[i]->get_type() == alive))
				std::cout << " alive ";
			if (enemies[i]->get_type() == undead) std::cout << " undead ";
			if (enemies[i]->get_type() == elemental) std::cout << " elemental ";
			std::cout << " name: " << enemies[i]->get_name() << std::endl;
			std::cout << "max HP: " << enemies[i]->get_max_HP();
			std::cout << " HP: " << enemies[i]->get_HP() << std::endl;
			std::cout << "damage: " << enemies[i]->get_damage();
			std::cout << " hit: " << enemies[i]->get_hit();
			std::cout << " x: " << enemies[i]->get_x();
			std::cout << " y: " << enemies[i]->get_y();
			std::cout << " experience: " << enemies[i]->get_experience();
			std::cout << " status: " << enemies[i]->get_status();
			Enemy *enemy = enemies[i];
			if ((enemies[i]->get_type() == dead) || (enemies[i]->get_type() == alive)) {
				Alive_Enemy *alive_enemy = dynamic_cast<Alive_Enemy*>(enemy);
				std::cout << " curse damage: " << alive_enemy->get_curse_damage();
				std::cout << " state:";
				if (alive_enemy->get_state() == dead) std::cout << " dead";
				else std::cout << " alive";
				std::cout << std::endl;
			}
			if (enemies[i]->get_type() == undead) {
				Undead *undead = dynamic_cast<Undead*>(enemy);
				std::cout << " name of alive: " << undead->get_name_of_alive() << std::endl;
			}
			if (enemies[i]->get_type() == elemental) {
				Elemental *elemental = dynamic_cast<Elemental*>(enemy);
				std::cout << " type(create): " << elemental->get_type_en()->get_name() << std::endl;
			}
			std::cout << std::endl;
		}
	}
}
void Level::show_controlled_undead() {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->get_type() == controlled_undead) {
			Enemy* enemy = enemies[i];
			Controlled_Undead *contrud = dynamic_cast<Controlled_Undead*>(enemy);
			std::cout << "name: " << enemies[i]->get_name();
			std::cout << " name of alive: " << contrud->get_name_of_alive() << std::endl;
			std::cout << "max HP: " << enemies[i]->get_max_HP();
			std::cout << " HP: " << enemies[i]->get_HP() << std::endl;
			std::cout << "damage: " << enemies[i]->get_damage();
			std::cout << " hit: " << enemies[i]->get_hit();
			std::cout << " x: " << enemies[i]->get_x();
			std::cout << " y: " << enemies[i]->get_y();
			std::cout << " status: " << enemies[i]->get_status();//?
			std::cout << " order: " << contrud->get_order() << std::endl;
		}
	std::cout << std::endl;
	}
}