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
    terrainMap_ = std::make_shared<TerrainMap>(40, 20);
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
        int dmg = combatSystem_->calculateDamage(*attacker, *target);
        combatSystem_->resolveCombat(*attacker, *target);
        notifyCombatResolved(attackerId, targetId, dmg);
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
        Resources loot(50, 20, 10);
        unit->addResources(loot);
        base_->addResources(loot);

        std::cout << "[Mediator] Unit " << unitId << " collected resources.\n";
        notifyResourceCollected(unitId, 50);
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
    if (!base_) return;

    Resources current = base_->getResources();
    Resources cost;

    if (from == "wood") {
        if (current.getWood() < amount) {
            std::cout << "[Mediator] Not enough wood! You have " << current.getWood() << ".\n";
            return;
        }
        cost = Resources(amount, 0, 0);
    }
    else if (from == "metal") {
        if (current.getMetal() < amount) {
            std::cout << "[Mediator] Not enough metal!\n";
            return;
        }
        cost = Resources(0, amount, 0);
    }
    else if (from == "energy") {
        if (current.getEnergy() < amount) {
            std::cout << "[Mediator] Not enough energy!\n";
            return;
        }
        cost = Resources(0, 0, amount);
    }
    else {
        std::cout << "[Mediator] Unknown resource type: " << from << "\n";
        return;
    }

    if (base_->spendResources(cost)) {
        std::cout << "[Mediator] Successfully distributed " << amount << " " << from << " to " << to << ".\n";
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