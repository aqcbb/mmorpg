#pragma once
#include "units/Unit.h"

class Scout : public Unit {
public:
    explicit Scout(int id, std::shared_ptr<ILogger> logger)
        : Unit(50, 2, 10, 0, 's', id, UnitTypeInfo::getInfo(UnitType::Scout), logger) {
    }
    std::string getType() const override { return "Scout"; }
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Scout>(*this); }
};