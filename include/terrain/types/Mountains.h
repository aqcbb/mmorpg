#pragma once
#include "terrain/Terrain.h"

class Mountain : public Terrain {
public:
	bool isPassable(UnitType type) const override {
		return type == UnitType::FlyingUnit;
	}

	double getSpeedModifier(UnitType type) const override {
		if (type == UnitType::FlyingUnit) return 0.5;
		return 0.0;
	}

	double getDefenseBonus(UnitType type) const override {
		return 0.0;
	}
};