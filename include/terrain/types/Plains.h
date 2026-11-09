#pragma once
#include "terrain/Terrain.h"

class Plains : public Terrain {
	bool isPassable(UnitType type) const override { 
		return true; 
	}
	
	double getSpeedModifier(UnitType type) const override { 
		return 1.0; 
	}
	
	double getDefenseBonus(UnitType type) const override { 
		return 0.0; 
	}
};