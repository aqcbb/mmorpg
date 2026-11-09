#include "terrain/TerrainProxy.h"
#include <iostream>

TerrainProxy::TerrainProxy(std::shared_ptr<Terrain> realTerrain) : realTerrain_(std::move(realTerrain)) {}

bool TerrainProxy::isPassable(UnitType type) const {
	if (type == UnitType::FlyingUnit) {
		std::cout << "[TerrainProxy] Flying unit passes freely\n";
		return true;
	}

	bool result = realTerrain_->isPassable(type);
	std::cout << "[TerrainProxy] isPassable(" << static_cast<int>(type) << ") = " << (result ? "true" : "false") << "\n";
	return result;
}

double TerrainProxy::getSpeedModifier(UnitType type) const {
	if (type == UnitType::FlyingUnit) {
		return 1.0;
	}
	return realTerrain_->getSpeedModifier(type);
}

double TerrainProxy::getDefenseBonus(UnitType type) const {
	return realTerrain_->getDefenseBonus(type);
}