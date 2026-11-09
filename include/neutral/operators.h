#pragma once
#include "units/Unit.h"
#include "neutral/objects/TreasureChest.h"
#include "neutral/objects/Trap.h"
#include "neutral/objects/Altar.h"
#include "neutral/objects/EnergySource.h"

inline Unit& operator+(Unit& unit, TreasureChest& chest) {
	chest.interact(unit);
	return unit;
}

inline Unit& operator-(Unit& unit, Trap& trap) {
	trap.interact(unit);
	return unit;
}

inline Unit& operator*(Unit& unit, Altar& altar) {
	altar.interact(unit);
	return unit;
}

inline Unit& operator/(Unit& unit, EnergySource& source) {
	source.interact(unit);
	return unit;
}