#include "Stairs.h"
int Stairs::get_type() {
	if (updown == up) return stairs_up;
	else return stairs_down;
}