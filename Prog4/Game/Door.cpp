#include "Door.h"
bool Door::close() {
	if (status == closed) return error;
	else {
		status = closed;
		return ok;
	}
}
bool Door::open() {
	if (status == opened) return error;
	else {
		status = opened;
		return ok;
	}
}
int Door::get_type() {
	if (status == closed) return closed_door;
	else return opened_door;
}