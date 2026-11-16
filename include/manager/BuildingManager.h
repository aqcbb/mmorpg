#pragma once
#include <memory>
#include <vector>
#include "building/Building.h"

class BuildingManager {
private:
    std::vector<std::shared_ptr<Building>> buildings_;
    int nextId_ = 1;
public:
    std::shared_ptr<Building> createBuilding(const std::string& type, int x, int y);
    void addBuilding(std::shared_ptr<Building> building);
    void updateAll();
    void printAllBuildings() const;
};