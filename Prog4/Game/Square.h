#pragma once
enum type { stairs_up, stairs_down, flooor, wall, opened_door, closed_door };
class Square {
public:
	Square() {};
	virtual int get_type() = 0;// squares[i][j].get_type()
	//virtual bool go() = 0; // мне кажется это лучше пусть геттайпом определяется
	virtual ~Square() {};
};