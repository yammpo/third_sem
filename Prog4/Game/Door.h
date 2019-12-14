#pragma once
#include "Square.h"
enum status { opened, closed };
enum result { error , ok };// ������������� ���� ����� ������
// error - ����� ��� ���� ������� / �������, ok - ��������� / ���������
class Door : public Square {
private:
	bool status;
public:
	Door(bool st = 0) : status(st) {};
	bool open();
	bool close();
	bool get_status() {return status; } // ������ ���� ��� ������ �������?
	void set_status(bool s) { status = s; }
	virtual int get_type();
	//virtual bool go();
	//~Door() {};
};
