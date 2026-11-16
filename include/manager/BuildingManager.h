#pragma once
#include <memory>
#include <vector>
#include "building/Building.h"

class BuildingManager {
private:
    std::vector<std::shared_ptr<Building>> buildings_;
    int nextId_ = 1;
public:
    std::shared_ptr<Building> buildBuilding(const std::string& type, int x, int y);
    void startResearch(const std::string& techId);
    void produceUnit(int buildingId, UnitType unitType);
    std::shared_ptr<Building> getBuildingById(int id) const;
    void updateAll();
    void printAllBuildings() const;
    const std::vector<std::shared_ptr<Building>>& getAllBuildings() const { return buildings_; }
};