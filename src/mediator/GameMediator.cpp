#include "mediator/GameMediator.h"
#include "base/Base.h"
#include "manager/UnitManager.h"
#include "manager/BuildingManager.h"
#include "combat/CombatSystem.h"
#include "resource/ResourceSystem.h"
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
}

void GameMediator::notifyUnitCreated(int unitId) {
    std::cout << "[Mediator] Unit " << unitId << " created and registered.\n";
}

void GameMediator::notifyCombatResolved(int attackerId, int targetId, int damage) {
    std::cout << "[Mediator] Unit " << attackerId << " attacked Unit " << targetId
        << " for " << damage << " damage.\n";
}

void GameMediator::moveUnit(int unitId, int x, int y) {
    unitManager_->moveUnit(unitId, x, y);
}