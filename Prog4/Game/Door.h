#pragma once
#include "Square.h"
enum status { opened, closed };
class Door : public Square {
private:
	bool status;
public:
	Door(bool st = 0) : status(st) {};
	void open() { status = opened; }
	void close() { status = closed; }
	bool get_status() {return status; } // нафига если это делает геттайп?
	void set_status(bool s) { status = s; }
	virtual int get_type() {
		if (status == closed) return closed_door;
		else return opened_door;
	}
	~Door() {};
};
