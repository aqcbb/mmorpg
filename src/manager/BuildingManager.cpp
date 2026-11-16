#include "manager/BuildingManager.h"
#include "building/types/Barracks.h"
#include "building/types/PowerPlant.h"
#include "building/types/Laboratory.h"
#include "building/types/Warehouse.h"
#include "building/types/Hospital.h"
#include <iostream>

std::shared_ptr<Building> BuildingManager::createBuilding(const std::string& type, int x, int y) {
    std::shared_ptr<Building> b;
    if (type == "Barracks") b = std::make_shared<Barracks>(nextId_++, x, y);
    else if (type == "PowerPlant") b = std::make_shared<PowerPlant>(nextId_++, x, y);
    else if (type == "Laboratory") b = std::make_shared<Laboratory>(nextId_++, x, y);
    else if (type == "Warehouse") b = std::make_shared<Warehouse>(nextId_++, x, y);
    else if (type == "Hospital") b = std::make_shared<Hospital>(nextId_++, x, y);
    if (b) buildings_.push_back(b);
    return b;
}

void BuildingManager::addBuilding(std::shared_ptr<Building> building) {
    buildings_.push_back(building);
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