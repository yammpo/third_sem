#pragma once
#include "Square.h"
enum status { opened, closed };
enum result { error , ok };// перекрашивать надо будет кстати
// error - дверь уже была закрыта / открыта, ok - открылась / закрылась
class Door : public Square {
private:
	bool status;
public:
	Door(bool st = 0) : status(st) {};
	bool open();
	bool close();
	bool get_status() {return status; } // нафига если это делает геттайп?
	void set_status(bool s) { status = s; }
	virtual int get_type();
	//virtual bool go();
	//~Door() {};
};
