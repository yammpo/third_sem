#include "Elemental.h"
Elemental& Elemental::operator = (const Elemental& el) {
	type = el.type;
	return *this;
}
Elemental::Elemental(const Elemental& el) {
	type = el.type;
}