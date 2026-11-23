#include "manager/UnitManager.h"
#include <iostream>
#include <algorithm>

void UnitManager::addUnit(std::shared_ptr<Unit> unit) {
    units_.push_back(unit);
}

void UnitManager::removeUnit(int unitId) {
    units_.erase(std::remove_if(units_.begin(), units_.end(),
        [unitId](const std::shared_ptr<Unit>& u) { return u->getId() == unitId; }), units_.end());
}

std::shared_ptr<Unit> UnitManager::getUnitById(int id) const {
    for (const auto& u : units_) {
        if (u->getId() == id) return u;
    }
    return nullptr;
}

bool UnitManager::moveUnit(int unitId, int x, int y) {
    auto unit = getUnitById(unitId);
    if (!unit) {
        if (logger_) logger_->log(LogEvent("ERROR", "UNIT", "Unit with ID " + std::to_string(unitId) + " not found"));
        return false;
    }

    unit->move(Point{ x, y });
    return true;
}

void UnitManager::printAllUnits() const {
    std::cout << "--- Units ---\n";
    for (const auto& u : units_) {
        std::cout << "ID: " << u->getId() << " | Type: " << u->getType()
            << " | HP: " << u->getHealth() << "\n";
    }
}