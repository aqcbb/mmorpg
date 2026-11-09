#include "controller/GameController.h"
#include "terrain/types/Forest.h"
#include "terrain/types/Mountains.h"
#include "terrain/types/Swamp.h"
#include "neutral/operators.h"
#include <iostream>
#include <stdexcept>

GameController::GameController(int width, int height)
	: base_(std::make_shared<Base>(1000, 20, 10)),
	terrain_(std::make_shared<TerrainMap>(width, height)),
	field_(width, height, 20) 
{
	objects_.resize(height);
	for (int y = 0; y < height; ++y) {
		objects_[y].resize(width);
	}
}

void GameController::setup() {
	terrain_->setTerrainAt(5, 5, std::make_shared<Forest>());
	terrain_->setTerrainAt(6, 5, std::make_shared<Forest>());
	terrain_->setTerrainAt(10, 11, std::make_shared<Mountains>());
	terrain_->setTerrainAt(2, 8, std::make_shared<Swamp>());

	objects_[1][1] = std::make_shared<TreasureChest>();
	objects_[3][8] = std::make_shared<Trap>();
	objects_[5][5] = std::make_shared<Altar>();
	objects_[9][9] = std::make_shared<EnergySource>();
}

void GameController::spawnUnit(UnitType type, int x, int y) {
	auto unit = base_->createUnit(type, x, y);
	if (unit) {
		field_.addUnit(unit, x, y);
	}
	else {
		std::cout << "Failed to spawn unit at " << x << ", " << y << "\n";
	}
}

std::shared_ptr<Unit> GameController::findUnit(int id) const {
	return base_->getUnitById(id);
}

void GameController::moveUnit(int unitId, int newX, int newY) {
	auto terr = terrain_->getTerrainAt(newX, newY);
	auto unit = findUnit(unitId);
	if (!unit) return;

	auto type = unit->getInfo()->type;
	if (!terr->isPassable(type)) {
		std::cout << "[GameController] Unit " << unitId << " cannot pass terrain!\n";
		return;
	}

	double speed = terr->getSpeedModifier(type);
	std::cout << "[GameController] Unit " << unitId << " moves with speed modifier " << speed << "\n";

	Point oldPos = unit->getPosition();
	field_.removeUnit(oldPos.x, oldPos.y);
	field_.addUnit(unit, newX, newY);
}

void GameController::interactWithObject(int unitId, int objX, int objY) {
	auto unit = findUnit(unitId);
	if (!unit) return;

	if (objX < 0 || objX >= objects_[0].size() || objY < 0 || objY >= objects_.size()) return;
	auto obj = objects_[objY][objX];
	if (!obj) {
		std::cout << "[GameController] No object at " << objX << ", " << objY << "\n";
		return;
	}

	if (auto chest = std::dynamic_pointer_cast<TreasureChest>(obj)) {
		*unit + *chest;
	}
	else if (auto trap = std::dynamic_pointer_cast<Trap>(obj)) {
		*unit - *trap;
	}
	else if (auto altar = std::dynamic_pointer_cast<Altar>(obj)) {
		*unit * *altar;
	}
	else if (auto source = std::dynamic_pointer_cast<EnergySource>(obj)) {
		*unit / *source;
	}
}

void GameController::drawField() const {
	field_.draw(std::cout);
}

void GameController::runCreationAndMovementScenario() {
	std::cout << "\nScenario 1: Creation & Movement\n";
	spawnUnit(UnitType::Infantry, 1, 1);
	spawnUnit(UnitType::Archer, 2, 1);
	drawField();
}

void GameController::runTerrainProxyScenario() {
	std::cout << "\nScenario 2: Terrain Proxy\n";

	auto unit = base_->createUnit(UnitType::Infantry, 10, 10);
	if (unit) {
		field_.addUnit(unit, 10, 10);
		moveUnit(unit->getId(), 10, 11);
	}
	
	auto flyer = base_->createUnit(UnitType::FlyingUnit, 11, 10);
	if (flyer) {
		field_.addUnit(flyer, 11, 10);
		moveUnit(flyer->getId(), 10, 11);
	}
}

void GameController::runNeutralObjectsScenario() {
	std::cout << "\nScenario 3: Neutral Objects\n";
	auto mage = base_->createUnit(UnitType::Mage, 8, 2);
	if (mage) {
		field_.addUnit(mage, 8, 2);
		std::cout << "Mage health before trap: " << mage->getHealth() << "\n";
		interactWithObject(mage->getId(), 8, 3);
		std::cout << "Mage health after trap: " << mage->getHealth() << "\n";
	}
}

void GameController::runObserverDeathScenario() {
	std::cout << "\nScenario 4: Observer Death\n";
	auto u = base_->createUnit(UnitType::Infantry, 3, 3);
	if (u) {
		field_.addUnit(u, 3, 3);
		std::cout << "Killing unit " << u->getId() << "...\n";
		u->takeDamage(9999);
		field_.removeUnit(3, 3);
		std::cout << "Base unit count: " << base_->getUnitCount() << "\n";
	}
}