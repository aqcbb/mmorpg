#pragma once
#include "units/Unit.h"

class Scout : public Unit {
public:
    explicit Scout(int id = 0)
        : Unit(50, 2, 10, 0, 's', id, UnitTypeInfo::getInfo(UnitType::Scout)) {
    }
    std::string getType() const override { return "Scout"; }
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Scout>(*this); }
};