#include "BD.h"
const char* MENU[]{ "1. Input number", "2. Show number", "3. Get complement code of nubmer", 
"4. Add number to your number","5. Substract number from your number", "6. Increase number in ten times",
"7. Decrease number in ten times", "0. Exit" };
const unsigned menuSZ = sizeof(MENU) / sizeof(MENU[0]);

int main() {
	unsigned menu = 1;
	const char*errmsg = "";
	bool work = true;
	Big_Decimal bd;
	Big_Decimal tmp;
	Big_Decimal bd1;
	Big_Decimal bd2;
	Big_Decimal res;
	bool overflow = false;
	std::cout << "Maximum number size is " << N - 1 << " digits" << std::endl;
	do {
		if (menu)
			for (size_t i = 0; i != menuSZ; ++i)
				std::cout << MENU[i] << std::endl;
		menu = GetNum(">>");
		switch (menu)
		{
		case 0:
			work = false;
			break;
		case 1:
			try { bd.Input(std::cin, bd, overflow); }
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			if (overflow == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
				overflow = false;
			}
			break;
		case 2:
			bd.Show(std::cout);
			break;
		case 3:
			tmp = bd.Complement_Code(bd);
			std::cout << "Complement code is" << std::endl;
			tmp.Show(std::cout);
			break;
		case 4:
			std::cout << "Enter number to add to your number" << std::endl;
			try { bd.Input(std::cin, bd1, overflow); } // мб вайлом пока не будет нормальное число?
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			if (overflow == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
				overflow = false;
			}
			res = bd.Addition(bd, bd1, overflow);
			if (overflow == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
				overflow = false;
			}
			res.Show(std::cout);
			break;
		case 5:
			std::cout << "Enter number to subtract from your number" << std::endl;
			try { bd.Input(std::cin, bd1, overflow); } // мб вайлом пока не будет нормальное число?
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			if (overflow == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
				overflow = false;
			}
			res = bd.Subtraction(bd, bd1, overflow);
			if (overflow == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
				overflow = false;
			}
			res.Show(std::cout);
			break;
		case 6:
			bd = bd.Increase(bd, overflow);
			if (overflow == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
				overflow = false;
			}
			std::cout << "x10 is" << std::endl;
			bd.Show(std::cout);
			break;
		case 7:
			bd = bd.Decrease(bd);
			std::cout << "/10 is" << std::endl;
			bd.Show(std::cout);
			break;
		default:
			std::cout << "Enter error, try again" << std::endl;
			break;
		}
		if (menu) {
			std::cout << "Enter 0 to continue, 1 to show the menu once again, ctrl+z to leave" << std::endl;
			do {
				std::cout << ">>";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> menu;
				if (std::cin.eof())
					work = false;
				else {
					if (!(std::cin.good()))
						std::cout << "Enter error, try again" << std::endl;
				}
			} while ((work) && !(std::cin.good()));
		}
	} while (work);
}