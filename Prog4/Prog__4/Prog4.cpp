#include "Dungeon.h"
int main(){
	Dungeon D(1);
	D.read_character();
	std::cout << "x: " << D.get_character().get_x() << std::endl;
	std::cout << "y: " << D.get_character().get_y() << std::endl;
	std::cout << "max mana: " << D.get_character().get_max_mana() << std::endl;
	std::cout << "mana: " << D.get_character().get_mana() << std::endl;
	std::cout << "max_HP: " << D.get_character().get_max_HP() << std::endl;
	std::cout << "HP: " << D.get_character().get_HP() << std::endl;
	std::cout << "experience: " << D.get_character().get_experience() << std::endl;
	std::cout << "level: " << D.get_character().get_level() << std::endl;
	std::cout << "max_controlled_undead: " << D.get_character().get_max_controlled_undead() << std::endl;
	D.read_levels();
	D.show(0);
	while (true) {
		char c;
		std::cin >> c;
		D.go_character(c);
		D.show(0);
	}
	return 0;
}