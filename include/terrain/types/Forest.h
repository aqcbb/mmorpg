#pragma once
#include "terrain/Terrain.h"

class Forest : public Terrain {
public:
	bool isPassable(UnitType type) const override {
		if (type == UnitType::Mage) return false;
		return true;
	}

	double getSpeedModifier(UnitType type) const override {
		if (type == UnitType::Infantry) return 0.5;
		return 0.8;
	}

	double getDefenseBonus(UnitType type) const override {
		if (type == UnitType::Infantry || type == UnitType::Archer) {
			return 0.2;
		}
		return 0.0;
	}
};