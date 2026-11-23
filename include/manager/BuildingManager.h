#pragma once
#include <memory>
#include <vector>
#include "building/Building.h"
#include "core/UnitType.h"
#include "logging/ILogger.h"

class BuildingManager {
private:
    std::vector<std::shared_ptr<Building>> buildings_;
    int nextId_ = 1;
    std::shared_ptr<ILogger> logger_;
public:
    explicit BuildingManager(std::shared_ptr<ILogger> logger) : logger_(logger) {}
    std::shared_ptr<Building> buildBuilding(const std::string& type, int x, int y);
    void startResearch(const std::string& techId);
    void produceUnit(int buildingId, UnitType unitType);
    std::shared_ptr<Building> getBuildingById(int id) const;
    void updateAll();
    void printAllBuildings() const;
    const std::vector<std::shared_ptr<Building>>& getAllBuildings() const { return buildings_; }
};