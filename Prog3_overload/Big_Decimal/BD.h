#pragma once
#include <cstring>
#include <iostream>
#pragma warning(disable:4996)
static const int N = 60; // max size
enum times { ten_times, minus_ten_times };
class Big_Decimal {
private:
	char value[N]; // value[0] - ���� ����� (0 +, 9 -)
	bool overflow; // ������������
public:
	Big_Decimal(); // ����������� �� ���������
	friend Big_Decimal operator + (Big_Decimal &, Big_Decimal &);//���� ���� ����
	friend Big_Decimal operator - (Big_Decimal &, Big_Decimal &);
	Big_Decimal String_To_Big_Decimal(char*); // �������� ������������ � ����������, ���� ������ ������������
	Big_Decimal Long_To_Big_Decimal(long int);
	// \0 ��������� ������ �����
	char Get_Value(int i) const { return value[i]; }
	bool Get_Overflow() const { return overflow; }
	Big_Decimal Complement_Code(Big_Decimal&);
	Big_Decimal operator () (bool);
	friend std::istream& operator >> (std::istream& s, Big_Decimal&);
	friend std::ostream& operator << (std::ostream& s, Big_Decimal&);
};
char* getstr(std::istream& s);
unsigned GetNum(const char* msg);
unsigned GetNum(const char* msg, std::istream& i);