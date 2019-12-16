#include "Dungeon.h"
#include <stdlib.h>
std::string go_errors[6] = { "error: end of field", "error: wall",
						"error: closed door","error: end of levels", "error: enemy", "you win!!!" };
std::string door_errors[3] = { "error: no door in this square", "error: door's already opened",
						"error: door's already closed"};
std::string skills_errors[7] = { "error: no enemy in this square", 
	"error: this skill can't be used to this enemy", "error: open parent before use",
	"error: u've got not enough mana", "error: ur level is too low", 
	"error: u already controlle max undeads", "error: u r healthy enough :)" };

int main(){
	Dungeon D(3);
	D.read_levels();
	D.read_character();
	std::cout << "level: " << D.get_level_number() << std::endl;
	D.show_characteristics();
	D.show_level(D.get_level_number());
	std::cout << std::endl;
	std::cout << "w - go up, a - go left, d - go right, s - go down" << std::endl;
	std::cout << "o - open a door, c - close a door" << std::endl;
	std::cout << "t - show skill table (to choose a skill to use)" << std::endl;
	std::cout << "v - show info about enemies" << std::endl;
	std::cout << "p - exit" << std::endl;
	// + сохраниться/ закончить/ начать сначала бла бла
	char choise;
	do {
		std::cin >> choise;
		//cin good проверить чар ли вообще ввели
		if ((choise == 'w') || (choise == 's') || (choise == 'a') || (choise == 'd')) {
			int i = D.go_character(choise);
			//if (i) std::cout << go_errors[i - 1] << std::endl;
			system("cls");
			std::cout << "level: " << D.get_level_number() + 1 << std::endl;
			D.show_characteristics();
			D.show_level(D.get_level_number());
			std::cout << std::endl;
			if (i) std::cout << go_errors[i - 1] << std::endl << std::endl;
			std::cout << "w - go up, a - go left, d - go right, s - go down" << std::endl;
			std::cout << "o - open a door, c - close a door" << std::endl;
			std::cout << "t - show skill table (to choose a skill to use)" << std::endl;
			std::cout << "v - show info about enemies" << std::endl;
			std::cout << "u - show info about controlled undeads" << std::endl;
		}
		else if (choise == 't') {
			D.show_skill_table();
			std::cout << std::endl;
			std::cout << "enter the direction(w, s, d, a) and index of skill u want to use" << std::endl;
			char c;
			int i;
			std::cin >> c;
			std::cin >> i;
			int t = D.use_skill(c, i); // проверить на ошибку ввода
			if (t) std::cout << skills_errors[t - 1] << std::endl << std::endl;
		}
		else if (choise == 'o') {
			char c;
			std::cout << "which door? (w, s, a, d)" << std::endl;
			std::cin >> c;// проверку на правильность
			int i = D.change_door(c, open);
			if (i) std::cout << door_errors[i - 1] << std::endl << std::endl;
		}
		else if (choise == 'c') {
			char c;
			std::cout << "which door? (w, s, a, d)" << std::endl;
			std::cin >> c;// проверку на правильность
			int i = D.change_door(c, close);
			if (i) std::cout << door_errors[i - 1] << std::endl << std::endl;
		}
		else if (choise == 'v') D.show_enemies(); 
		else if (choise == 'u') D.show_controlled_undead();
		else std::cout << "no such command" << std::endl;
	} while (choise != 'p');
	return 0;
}