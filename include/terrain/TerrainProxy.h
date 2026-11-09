#pragma once

#include "Terrain.h"
#include <memory>

class TerrainProxy : public Terrain {
private:
	std::shared_ptr<Terrain> realTerrain_;
public:
	explicit TerrainProxy(std::shared_ptr<Terrain> realTerrain);

	bool isPassable(UnitType type) const override;
	double getSpeedModifier(UnitType type) const override;
	double getDefenseBonus(UnitType type) const override;
};