#include "terrain/TerrainProxy.h"

TerrainProxy::TerrainProxy(std::shared_ptr<Terrain> realTerrain) : realTerrain_(std::move(realTerrain)) {}

bool TerrainProxy::isPassable(UnitType type) const {
	return realTerrain_->isPassable(type);
}

double TerrainProxy::getSpeedModifier(UnitType type) const {
	return realTerrain_->getSpeedModifier(type);
}

double TerrainProxy::getDefenseBonus(UnitType type) const {
	return realTerrain_->getDefenseBonus(type);
}