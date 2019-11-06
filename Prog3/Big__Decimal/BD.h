#pragma once
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)
static const int N = 60; // max size
class Big_Decimal {
private:
	char value[N]; // value[0] - знак числа (0 +, 9 -)
public:
	Big_Decimal(); // конструктор по умолчанию // +
	Big_Decimal String_To_Big_Decimal(char*, bool&); // возможно переполнение и исключение, если строка некорректная //+
	Big_Decimal Long_To_Big_Decimal(long int, bool&); // +
	// \0 добавлять видимо самой
	char Get_Value(int i) const { return value[i]; } // +
	//int Get_N() const { return N; }
	Big_Decimal Complement_Code(Big_Decimal&); // +
	Big_Decimal Addition(Big_Decimal&, Big_Decimal&, bool&); // +
	Big_Decimal Subtraction(Big_Decimal&, Big_Decimal&, bool&); // +
	Big_Decimal Increase(Big_Decimal&, bool&); // +
	Big_Decimal Decrease(Big_Decimal&); // +
	std::istream& Input(std::istream& s, Big_Decimal&, bool&);
	std::ostream& Show(std::ostream& s);
};
char* getstr(std::istream& s);
unsigned GetNum(const char* msg);
unsigned GetNum(const char* msg, std::istream& i);