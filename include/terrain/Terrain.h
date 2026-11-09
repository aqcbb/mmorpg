#pragma once

#include "core/UnitType.h"

class Terrain {
public:
	virtual ~Terrain() = default;

	virtual bool isPassable(UnitType type) const = 0;
	virtual double getSpeedModifier(UnitType type) const = 0;
	virtual double getDefenseBonus(UnitType type) const = 0;
	virtual char getSymbol() const = 0;
};