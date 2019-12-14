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
void Level::read_squares(std::string way) {
	std::ifstream lev(way);
	if (!lev.is_open()) throw std::runtime_error("File can't open!");
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
				if (c == '.') square = new Floor(); // не уверена
				if (c == '#') square = new Wall();
				if (c == '>') {
					square = new Stairs();
					Stairs *stairs = dynamic_cast<Stairs*>(square); 
					stairs->set_updown(down);
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
}