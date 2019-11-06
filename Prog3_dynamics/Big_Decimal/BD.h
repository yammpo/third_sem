#pragma once
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)
static const int N = 60; // max size
enum times { ten_times, minus_ten_times };
enum which_side { begin, end };
class Big_Decimal {
private:
	char *value; // value[0] - знак числа (0 +, 9 -)
	int n; // разрядная сетка числа (длина числа + 1)
	bool overflow; // переполнение
public:
	Big_Decimal(); // конструктор по умолчанию
	Big_Decimal(const Big_Decimal&); // копирующий конструктор
	Big_Decimal(Big_Decimal&&); // перемещающий конструктор
	~Big_Decimal() { delete[] value; n = 0; overflow = false; }// деструктор
	Big_Decimal& operator = (const Big_Decimal&); // копирующее равно
	Big_Decimal& operator = (Big_Decimal&&); // перемещающее равно 
	friend Big_Decimal operator + (Big_Decimal &, Big_Decimal &);//куда деть флаг
	friend Big_Decimal operator - (Big_Decimal &, Big_Decimal &);
	Big_Decimal String_To_Big_Decimal(char*); // возможно переполнение и исключение, если строка некорректная
	Big_Decimal Long_To_Big_Decimal(long int);
	// \0 добавлять видимо самой
	char Get_Value(int i) const { return value[i]; }
	bool Get_Overflow() const { return overflow; }
	int Get_n() const { return n; }
	Big_Decimal Complement_Code(Big_Decimal&);
	Big_Decimal operator () (bool);
	friend std::istream& operator >> (std::istream& s, Big_Decimal&);
	friend std::ostream& operator << (std::ostream& s, Big_Decimal&);
	friend char* Realloc(char*, unsigned, unsigned, bool);
};
char* getstr(std::istream& s);
unsigned GetNum(const char* msg);
unsigned GetNum(const char* msg, std::istream& i);