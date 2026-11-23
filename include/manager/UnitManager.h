#pragma once
#include <memory>
#include <vector>
#include "units/Unit.h"
#include "logging/ILogger.h"

class UnitManager {
private:
    std::vector<std::shared_ptr<Unit>> units_;
    std::shared_ptr<ILogger> logger_;
public:
    UnitManager(std::shared_ptr<ILogger> logger) : logger_(logger) {}
    void addUnit(std::shared_ptr<Unit> unit);
    void removeUnit(int unitId);
    std::shared_ptr<Unit> getUnitById(int id) const;
    bool moveUnit(int unitId, int x, int y);
    const std::vector<std::shared_ptr<Unit>>& getAllUnits() const { return units_; }
    void printAllUnits() const;
};