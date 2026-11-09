#pragma once
#include "terrain/Terrain.h"

class Swamp : public Terrain {
public:
	bool isPassable(UnitType type) const override {
		return true;
	}

	double getSpeedModifier(UnitType type) const override {
		return 0.3;
	}

	double getDefenseBonus(UnitType type) const override {
		return 0.0;
	}

	char getSymbol() const override { return '~'; }
};