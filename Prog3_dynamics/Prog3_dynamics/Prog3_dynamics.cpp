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
			//try { bd.Input(std::cin, bd); }
			try { std::cin >> bd; }
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			if (bd.Get_Overflow() == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
			}
			break;
		case 2:
			//bd.Show(std::cout);
			std::cout << bd;
			break;
		case 3:
			tmp = bd.Complement_Code(bd);
			std::cout << "Complement code is" << std::endl;
			std::cout << tmp;
			break;
		case 4:
			std::cout << "Enter number to add to your number" << std::endl;
			try { std::cin >> bd1; } // мб вайлом пока не будет нормальное число?
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			if (bd1.Get_Overflow() == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
			}
			res = bd + bd1;
			//res = bd.Addition(bd, bd1, overflow);
			if (res.Get_Overflow() == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
			}
			std::cout << res;
			break;
		case 5:
			std::cout << "Enter number to subtract from your number" << std::endl;
			try { std::cin >> bd1; } // мб вайлом пока не будет нормальное число?
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			if (bd1.Get_Overflow() == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
			}
			res = bd - bd1;
			//res = bd.Subtraction(bd, bd1, overflow);
			if (res.Get_Overflow() == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
			}
			std::cout << res;
			break;
		case 6:
			bd(ten_times);
			if (bd.Get_Overflow() == true) {
				std::cout << "Sorry, overflow occured. Recorded all that fit" << std::endl;
			}
			std::cout << "x10 is" << std::endl;
			std::cout << bd;
			break;
		case 7:
			bd(minus_ten_times);
			std::cout << "/10 is" << std::endl;
			std::cout << bd;
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