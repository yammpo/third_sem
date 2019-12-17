#pragma once
#include "Undead.h"
#include "Elemental.h"
class Super_Undead : public Undead, public Elemental {
public:
	Super_Undead();
	~Super_Undead() {};
};