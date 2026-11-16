#pragma once
#include <memory>
#include <vector>
#include "units/Unit.h"

class UnitManager {
private:
    std::vector<std::shared_ptr<Unit>> units_;
public:
    void addUnit(std::shared_ptr<Unit> unit);
    void removeUnit(int unitId);
    std::shared_ptr<Unit> getUnitById(int id) const;
    bool moveUnit(int unitId, int x, int y);
    void printAllUnits() const;
};