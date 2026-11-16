#include "mediator/GameMediator.h"
#include "base/Base.h"
#include "manager/UnitManager.h"
#include "manager/BuildingManager.h"
#include "combat/CombatSystem.h"
#include "resource/ResourceSystem.h"
#include "units/Unit.h"
#include <iostream>

GameMediator::GameMediator() {
    base_ = std::make_shared<Base>(1000, 50, 5);
    unitManager_ = std::make_shared<UnitManager>();
    buildingManager_ = std::make_shared<BuildingManager>();
    resourceSystem_ = std::make_shared<ResourceSystem>();
    combatSystem_ = std::make_shared<CombatSystem>();
}

void GameMediator::createUnit(UnitType type, int x, int y) {
    auto unit = base_->createUnit(type, x, y);
    if (unit) {
        unitManager_->addUnit(unit);
        notifyUnitCreated(unit->getId());
    }
    else {
        std::cout << "[Mediator] Failed to create unit (limit reached or error).\n";
    }
}

void GameMediator::moveUnit(int unitId, int x, int y) {
    unitManager_->moveUnit(unitId, x, y);
}

void GameMediator::attack(int attackerId, int targetId) {
    auto attacker = unitManager_->getUnitById(attackerId);
    auto target = unitManager_->getUnitById(targetId);

    if (attacker && target) {
        combatSystem_->resolveCombat(*attacker, *target);
        notifyCombatResolved(attackerId, targetId, 20);
        if (!target->isAlive()) {
            unitManager_->removeUnit(targetId);
            base_->removeUnit(targetId);
        }
    }
    else {
        std::cout << "[Mediator] Attacker or target not found.\n";
    }
}

void GameMediator::collectResource(int unitId, int resourcePointId) {
    auto unit = unitManager_->getUnitById(unitId);
    if (unit) {
        Resources loot(10, 5, 0);
        unit->addResources(loot);
        notifyResourceCollected(unitId, 15);
    }
    else {
        std::cout << "[Mediator] Unit not found.\n";
    }
}

void GameMediator::heal(int unitId, int targetId) {
    auto unit = unitManager_->getUnitById(unitId);
    auto target = unitManager_->getUnitById(targetId);
    if (unit && target) {
        target->heal(30);
        std::cout << "[Mediator] Unit " << unitId << " healed Unit " << targetId << " for 30 HP.\n";
    }
    else {
        std::cout << "[Mediator] Unit not found.\n";
    }
}

void GameMediator::buildBuilding(const std::string& type, int x, int y) {
    auto b = buildingManager_->buildBuilding(type, x, y);
    if (b) {
        base_->addBuilding(b);
    }
}

void GameMediator::research(const std::string& techId) {
    buildingManager_->startResearch(techId);
}

void GameMediator::distributeResources(const std::string& from, const std::string& to, int amount) {
    std::cout << "[Mediator] Distributed " << amount << " resources from " << from << " to " << to << ".\n";
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
    std::cout << "[Mediator] Unit " << unitId << " created and registered.\n";
}

void GameMediator::notifyResourceCollected(int unitId, int amount) {
    std::cout << "[Mediator] Unit " << unitId << " collected " << amount << " resources.\n";
}

void GameMediator::notifyCombatResolved(int attackerId, int targetId, int damage) {
    std::cout << "[Mediator] Unit " << attackerId << " attacked Unit "
        << targetId << " for " << damage << " damage.\n";
}

void GameMediator::notifyBuildingCompleted(int buildingId) {
    std::cout << "[Mediator] Building " << buildingId << " is completed.\n";
}

void GameMediator::notifyResearchCompleted(const std::string& tech) {
    std::cout << "[Mediator] Research " << tech << " completed.\n";
}