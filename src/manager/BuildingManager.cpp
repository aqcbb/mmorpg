#include "manager/BuildingManager.h"
#include "building/types/Barracks.h"
#include "building/types/PowerPlant.h"
#include "building/types/Laboratory.h"
#include "building/types/Warehouse.h"
#include "building/types/Hospital.h"
#include "core/UnitType.h"
#include <iostream>
#include <algorithm>

std::shared_ptr<Building> BuildingManager::buildBuilding(const std::string& type, int x, int y) {
    std::shared_ptr<Building> b;
    if (type == "Barracks" || type == "barracks")
        b = std::make_shared<Barracks>(nextId_++, x, y);
    else if (type == "PowerPlant" || type == "powerplant")
        b = std::make_shared<PowerPlant>(nextId_++, x, y);
    else if (type == "Laboratory" || type == "laboratory")
        b = std::make_shared<Laboratory>(nextId_++, x, y);
    else if (type == "Warehouse" || type == "warehouse")
        b = std::make_shared<Warehouse>(nextId_++, x, y);
    else if (type == "Hospital" || type == "hospital")
        b = std::make_shared<Hospital>(nextId_++, x, y);
    else {
        std::cout << "[BuildingManager] Unknown building type: " << type << "\n";
        return nullptr;
    }

    buildings_.push_back(b);
    std::cout << "[BuildingManager] Started building " << type << " at (" << x << ", " << y << ")\n";
    return b;
}

void BuildingManager::startResearch(const std::string& techId) {
    std::cout << "[BuildingManager] Started research: " << techId << "\n";
}

void BuildingManager::produceUnit(int buildingId, UnitType unitType) {
    auto b = getBuildingById(buildingId);
    if (b) {
        std::cout << "[BuildingManager] Building " << buildingId << " produced unit type " << static_cast<int>(unitType) << "\n";
    }
    else {
        std::cout << "[BuildingManager] Building " << buildingId << " not found.\n";
    }
}

std::shared_ptr<Building> BuildingManager::getBuildingById(int id) const {
    for (const auto& b : buildings_) {
        if (b->getId() == id) return b;
    }
    return nullptr;
}

void BuildingManager::updateAll() {
    for (auto& b : buildings_) b->update();
}

void BuildingManager::printAllBuildings() const {
    std::cout << "--- Buildings ---\n";
    for (const auto& b : buildings_) {
        std::cout << "ID: " << b->getId() << " | Type: " << b->getType()
            << " | Progress: " << b->getBuildProgress() << "%\n";
    }
}