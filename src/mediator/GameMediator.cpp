#include "mediator/GameMediator.h"
#include "base/Base.h"
#include "manager/UnitManager.h"
#include "manager/BuildingManager.h"
#include "combat/CombatSystem.h"
#include "resource/ResourceSystem.h"
#include "units/Unit.h"
#include "logging/LogEvent.h"
#include "neutral/objects/TreasureChest.h"
#include "neutral/objects/Trap.h"
#include "neutral/objects/Altar.h"
#include "neutral/objects/EnergySource.h"
#include "logging/LogEvent.h"
#include <iostream>

GameMediator::GameMediator(std::shared_ptr<ILogger> logger) : logger_(logger) {
    base_ = std::make_shared<Base>(1000, 50, 5, logger_);

    unitManager_ = std::make_shared<UnitManager>(logger_);
    buildingManager_ = std::make_shared<BuildingManager>(logger_);

    resourceSystem_ = std::make_shared<ResourceSystem>();
    combatSystem_ = std::make_shared<CombatSystem>(logger_);

    terrainMap_ = std::make_shared<TerrainMap>(40, 20, logger_);
    terrainMap_->generateRandomTerrain();

    gameField_ = std::make_shared<GameField>(40, 20, 100);
}

void GameMediator::createUnit(UnitType type, int x, int y) {
    if (!gameField_ || !gameField_->inBounds(x, y)) {
        if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Cannot create unit: out of bounds"));
        return;
    }

    auto unit = base_->createUnit(type, x, y);
    if (unit) {
        unitManager_->addUnit(unit);
        notifyUnitCreated(unit->getId());
    }
    else {
        if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Failed to create unit (limit reached)"));
    }
}

void GameMediator::moveUnit(int unitId, int x, int y) {
    if (!gameField_ || !gameField_->inBounds(x, y)) {
        if (logger_) logger_->log(LogEvent("ERROR", "UNIT", "Cannot move unit: out of bounds"));
        return;
    }

    for (const auto& b : buildingManager_->getAllBuildings()) {
        if (b->getX() == x && b->getY() == y) {
            if (logger_) logger_->log(LogEvent("ERROR", "UNIT", "Cannot move unit: building '" + b->getType() + "' is on this cell!"));
            return;
        }
    }

    auto unit = unitManager_->getUnitById(unitId);
    if (!unit) {
        if (logger_) logger_->log(LogEvent("ERROR", "UNIT", "Unit not found"));
        return;
    }


    unitManager_->moveUnit(unitId, x, y);

    if (auto obj = getObjectAt(x, y)) {
        if (logger_) {
            logger_->log(LogEvent("INFO", "ENV", "Unit " + std::to_string(unitId) + " stepped on a neutral object!"));
        }
        obj->interact(*unit);

        objects_[y][x] = nullptr; 
    }
}

void GameMediator::spawnObject(const std::string& type, int x, int y) {
    if (!gameField_ || !gameField_->inBounds(x, y)) {
        if (logger_) logger_->log(LogEvent("ERROR", "ENV", "Cannot spawn object: out of bounds"));
        return;
    }

    std::shared_ptr<NeutralObject> obj;
    if (type == "chest") obj = std::make_shared<TreasureChest>(logger_);
    else if (type == "trap") obj = std::make_shared<Trap>(logger_);
    else if (type == "altar") obj = std::make_shared<Altar>(logger_);
    else if (type == "source") obj = std::make_shared<EnergySource>(logger_);
    else {
        if (logger_) logger_->log(LogEvent("ERROR", "ENV", "Unknown object type: " + type));
        return;
    }

    if (objects_.size() <= y) objects_.resize(y + 1);
    if (objects_[y].size() <= x) objects_[y].resize(x + 1);

    objects_[y][x] = obj;
    if (logger_) logger_->log(LogEvent("INFO", "ENV", "Spawned " + type + " at (" + std::to_string(x) + "," + std::to_string(y) + ")"));
}

std::shared_ptr<NeutralObject> GameMediator::getObjectAt(int x, int y) const {
    if (!gameField_ || !gameField_->inBounds(x, y)) return nullptr;

    if (y >= objects_.size() || x >= objects_[y].size()) return nullptr;

    return objects_[y][x];
}

void GameMediator::attack(int attackerId, int targetId) {
    auto attacker = unitManager_->getUnitById(attackerId);
    auto target = unitManager_->getUnitById(targetId);

    if (attacker && target) {
        int dmg = combatSystem_->calculateDamage(*attacker, *target);
        combatSystem_->resolveCombat(*attacker, *target);
        notifyCombatResolved(attackerId, targetId, dmg);
        if (!target->isAlive()) {
            unitManager_->removeUnit(targetId);
            base_->removeUnit(targetId);
        }
    }
    else {
        if (logger_) logger_->log(LogEvent("ERROR", "COMBAT", "Attacker or target not found"));
    }
}

void GameMediator::collectResource(int unitId, int resourcePointId) {
    auto unit = unitManager_->getUnitById(unitId);
    if (unit) {
        Resources loot(50, 20, 10);
        unit->addResources(loot);
        base_->addResources(loot);
        notifyResourceCollected(unitId, 50);
    }
    else {
        if (logger_) logger_->log(LogEvent("ERROR", "UNIT", "Unit not found for collecting"));
    }
}

void GameMediator::heal(int unitId, int targetId) {
    auto unit = unitManager_->getUnitById(unitId);
    auto target = unitManager_->getUnitById(targetId);
    if (unit && target) {
        target->heal(30);
    }
    else {
        if (logger_) logger_->log(LogEvent("ERROR", "UNIT", "Healer or target not found"));
    }
}

void GameMediator::buildBuilding(const std::string& type, int x, int y) {
    if (!gameField_ || !gameField_->inBounds(x, y)) {
        if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Cannot build: out of bounds"));
        return;
    }

    auto b = buildingManager_->buildBuilding(type, x, y);
    if (b) {
        base_->addBuilding(b);
    }
}

void GameMediator::research(const std::string& techId) {
    buildingManager_->startResearch(techId);
}

void GameMediator::distributeResources(const std::string& from, const std::string& to, int amount) {
    if (!base_) return;

    Resources current = base_->getResources();
    Resources cost;

    if (from == "wood") {
        if (current.getWood() < amount) {
            if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Not enough wood"));
            return;
        }
        cost = Resources(amount, 0, 0);
    }
    else if (from == "metal") {
        if (current.getMetal() < amount) {
            if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Not enough metal"));
            return;
        }
        cost = Resources(0, amount, 0);
    }
    else if (from == "energy") {
        if (current.getEnergy() < amount) {
            if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Not enough energy"));
            return;
        }
        cost = Resources(0, 0, amount);
    }
    else {
        if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Unknown resource type"));
        return;
    }

    if (base_->spendResources(cost)) {
        if (logger_) logger_->log(LogEvent("INFO", "BASE", "Distributed " + std::to_string(amount) + " " + from + " to " + to));
        notifyResourceCollected(0, amount);
    }
}

void GameMediator::produceUnit(int buildingId, UnitType type) {
    buildingManager_->produceUnit(buildingId, type);
}

void GameMediator::getStats() const {
    std::cout << "\n[GAME STATS]\n";
    unitManager_->printAllUnits();
    buildingManager_->printAllBuildings();
    std::cout << "Base HP: " << base_->getHealth() << " | Base Resources: ";
    base_->getResources().print();
    std::cout << "\n";
}

void GameMediator::notifyUnitCreated(int unitId) {
    if (logger_) logger_->log(LogEvent("INFO", "BASE", "Unit " + std::to_string(unitId) + " created and registered"));
}

void GameMediator::notifyResourceCollected(int unitId, int amount) {
    if (logger_) logger_->log(LogEvent("INFO", "UNIT", "Unit " + std::to_string(unitId) + " collected " + std::to_string(amount) + " resources"));
}

void GameMediator::notifyCombatResolved(int attackerId, int targetId, int damage) {
    if (logger_) logger_->log(LogEvent("INFO", "COMBAT", "Unit " + std::to_string(attackerId) + " attacked Unit " + std::to_string(targetId) + " for " + std::to_string(damage) + " damage"));
}

void GameMediator::notifyBuildingCompleted(int buildingId) {
    std::cout << "[Mediator] Building " << buildingId << " is completed.\n";
}

void GameMediator::notifyResearchCompleted(const std::string& tech) {
    std::cout << "[Mediator] Research " << tech << " completed.\n";
}