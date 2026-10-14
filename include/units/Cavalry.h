#pragma once
#include "Unit.h"

class Cavalry : public Unit {
public:
	Cavalry(int hp, int arm, int dmg, char sym) : Unit(hp, arm, dmg, sym) {}
};