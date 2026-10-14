#pragma once
#include "Unit.h"

class Infantry : public Unit {
public:
	Infantry(int hp, int arm, int dmg, int sym) : Unit(hp, arm, dmg, sym) {}
};