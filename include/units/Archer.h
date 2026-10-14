#pragma once
#include "Unit.h"

class Archer : public Unit {
public:
	Archer(int hp, int arm, int dmg, char sym) : Unit(hp, arm, dmg, sym) {}
};