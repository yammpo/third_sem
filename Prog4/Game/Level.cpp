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
	if (!enemies.empty()) {
		//for (int i = 0; i < enemies.size(); i++) if (enemies[i]) delete enemies[i];
		//for (auto p : enemies) delete p;
		enemies.clear();
	}
	if (!squares.empty()) {
		for (int i = 0; i < h; i++) {
			//for (int j = 0; j < w; j++) if (squares[i][j]) delete[] squares[i][j];
			squares[i].clear();
		}
		squares.clear();
	}
}
Level& Level::operator = (const Level& lev) {
	h = lev.h;
	w = lev.w;
	squares.reserve(h);
	for (int i = 0; i < h; i++) {
		std::vector<Square*> vec;
		vec.reserve(w);
		for (int j = 0; j < w; j++) {
			Square *square = lev.squares[i][j];
			vec.push_back(square);
		}
		squares.push_back(vec);
	}
	enemies.reserve(lev.enemies.size());
	for (int i = 0; i < lev.enemies.size(); i++) {
		Enemy *enemy = lev.enemies[i];
		enemies.push_back(enemy);
	}
	return *this;
}
 Level::Level(const Level& lev) {
	h = lev.h;
	w = lev.w;
	squares.reserve(h);
	for (int i = 0; i < h; i++) {
		std::vector<Square*> vec;
		vec.reserve(w);
		for (int j = 0; j < w; j++) {
			Square *square = lev.squares[i][j];
			vec.push_back(square);
		}
		squares.push_back(vec);
	}
	enemies.reserve(lev.enemies.size());
	for (int i = 0; i < lev.enemies.size(); i++) {
		Enemy *enemy = lev.enemies[i];
		enemies.push_back(enemy);
	}
}
Level& Level::operator = (Level&& lev) {
	h = lev.h;
	w = lev.w;
	squares = lev.squares;
	enemies = lev.enemies;
	for (int i = 0; i < lev.enemies.size(); i++) delete[] lev.enemies[i];
	lev.enemies.clear();
	for (int i = 0; i < lev.h; i++) {
		for (int j = 0; j < lev.w; j++) delete[] lev.squares[i][j];
		lev.squares[i].clear();
	}
	lev.squares.clear();
	return *this;
}
Level::Level(Level&& lev) {
	h = lev.h;
	w = lev.w;
	squares = lev.squares;
	enemies = lev.enemies;
	for (int i = 0; i < lev.enemies.size(); i++) delete[] lev.enemies[i];
	lev.enemies.clear();
	for (int i = 0; i < lev.h; i++) {
		for (int j = 0; j < lev.w; j++) delete[] lev.squares[i][j];
		lev.squares[i].clear();
	}
	lev.squares.clear();
}
void Level::read_squares(std::string way) {
	std::ifstream lev(way);
	if (!lev.is_open()) throw std::runtime_error("File can't open!");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) if (squares[i][j]) delete[] squares[i][j];
		if (!squares[i].empty()) squares[i].clear();
	}
	if (!squares.empty()) squares.clear();
	int hh, ww;
	lev >> hh;
	h = hh;
	lev >> ww;
	w = ww;
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
	//squares.reserve(h);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int type = squares[i][j]->get_type();
			if (type == flooor) { lev << "."; if (w - 1 > j)  lev << " "; }
			if (type == wall) { lev << "#"; if (w - 1 > j)  lev << " "; }
			if (type == stairs_down) { lev << ">"; if (w - 1 > j)  lev << " "; }
			if (type == stairs_up) { lev << "<"; if (w - 1 > j)  lev << " "; }
			if (type == opened_door) { lev << "/"; if (w - 1 > j)  lev << " "; }
			if (type == closed_door) { lev << "+"; if (w - 1 > j)  lev << " "; }
			if (type == winner) { lev << "$"; if (w - 1 > j)  lev << " "; }
		}
		if (h - 1 > i ) lev << std::endl;
	}
	lev.close();
}
void Level::read_enemies(std::string way) {
	std::ifstream enem(way);
	for (int i = 0; i < enemies.size(); i++) if (enemies[i] != nullptr) delete[] enemies[i];
	if (!enemies.empty()) enemies.clear(); 
	if (!enem.is_open()) throw std::runtime_error("File can't open!");
	int number_of_enemies;
	enem >> number_of_enemies;
	//if (!enemies.empty()) enemies.clear();
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
	if (enemies.size() > 0) enem << enemies.size() << std::endl;
	else enem << enemies.size();
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
		if (enemies.size() - 1 > i ) enem << std::endl;
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
bool Level::check_wall(int y, int x) {
	int type = squares[y][x]->get_type();
	for (int i = 0; i < enemies.size(); i++) {
		if ((enemies[i]->get_x() == x) && (enemies[i]->get_y() == y))
			return the_wall;
	}
	//if (y == ch_y && x == ch_x) return the_wall;
	if ((type == flooor) || (type == opened_door)) return the_blank;// про дверь подумать
	//и если на клетке нет врагов(других?) и песонажа(ммм а персонажа то я где возьму)
	//видимо нигде, но тогда могут быть проблемы с подконтрольной нежитью. ОСТОРОЖНО
	else return the_wall;
}
std::vector<std::vector<int>> Level::squares_to_ints() {
	std::vector<std::vector<int>> grid;
	grid.reserve(h);
	for (int i = 0; i < h; i++) {
		std::vector<int> vec;
		vec.reserve(w);
		for (int j = 0; j < w; j++) {
			int k;
			if (check_wall(i, j) == the_wall) k = -1;
			else k = -2;
			vec.push_back(k);
		}
		grid.push_back(vec);
	}
	return grid;
}
bool Level::lee(int ax, int ay, int bx, int by, std::vector<int>&px, std::vector<int>&py)   // поиск пути из ячейки (ax, ay) в ячейку (bx, by)
{
	std::vector<std::vector<int>> grid = squares_to_ints();
	// проверить не лежит ли ax, ay в окрестности bx, by
	// если лежит никуда не идти (или атаковать)
	int dx[4] = { 1, 0, -1, 0 };   // смещения, соответствующие соседям ячейки
	int dy[4] = { 0, 1, 0, -1 };   // справа, снизу, слева и сверху
	int d, x, y, k;
	int len;
	for (int okr = 0; okr < 4; ++okr) {
		int okry = by + dy[okr], okrx = bx + dx[okr];
		if (okry >= 0 && okry < h && okrx >= 0 && okrx < w && okry == ay && okrx == ax)
			return false;
	}
	//std::vector<int> px, py;
	px.reserve(w*h);
	py.reserve(w*h);
	px.resize(w*h);
	py.resize(w*h);
	px.push_back(ax);
	py.push_back(ay);
	//int px[W * H], py[W * H];
	bool stop;

	//if ((grid[ay][ax] == WALL || grid[by][bx] == WALL)) return false;  // ячейка (ax, ay) или (bx, by) - стена

	// распространение волны
	d = 0;
	grid[ay][ax] = 0;            // стартовая ячейка помечена 0
	do {
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < h; ++y)
			for (x = 0; x < w; ++x)
				if (grid[y][x] == d)                         // ячейка (x, y) помечена числом d
				{
					for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным соседям
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < h && ix >= 0 && ix < w &&
							grid[iy][ix] == BLANK)
						{
							stop = false;              // найдены непомеченные клетки
							grid[iy][ix] = d + 1;      // распространяем волну
						}
					}
				}
		d++;
	} while (!stop && grid[by][bx] == BLANK);

	if (grid[by][bx] == BLANK) return false;  // путь не найден

	// восстановление пути
	len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
	x = bx;
	y = by;
	d = len;
	while (d > 0)
	{
		px.insert(px.begin() + d, x); // думаю можно только первый шаг записать
		py.insert(py.begin() + d, y); // так как остальными я не пользуюсь
		//px[d] = x;
		//py[d] = y;                   // записываем ячейку (x, y) в путь
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = y + dy[k], ix = x + dx[k];
			if (iy >= 0 && iy < h && ix >= 0 && ix < w &&
				grid[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
				break;
			}
		}
	}
	//px[0] = ax;
	//py[0] = ay;                    // теперь px[0..len] и py[0..len] - координаты ячеек пути
	return true;
}
void Level::go_enemy(int x, int y) {
	std::vector<int> px, py;
	for (int j = 0; j < enemies.size(); j++) { // сделать чтоб трупы и controlled_undead не ходили
		if (enemies[j]->get_type() != controlled_undead &&
			enemies[j]->get_type() != dead) {
			int en_x = enemies[j]->get_x();
			int en_y = enemies[j]->get_y();
			if (lee(en_x, en_y, x, y, px, py) == true) {
				enemies[j]->set_x(px[1]);
				enemies[j]->set_y(py[1]);
				// крч получаем последовательность ходов (из lee вытастикаем, по ссылке)
				// и собственно ходим (меняем координаты врага последовательно х и у)
				// ходим каждый раз видимо только на одну штуку из этой последовательности
				// но тогда нам как будто нет смысла запоминать всю последовательность, надо запоминать 
				// только первый шаг
			}
		}
	}
}