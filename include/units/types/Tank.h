#pragma once
#include "units/Unit.h"

class Tank : public Unit {
public:
    explicit Tank(int id = 0)
        : Unit(200, 20, 40, 0, 'T', id, UnitTypeInfo::getInfo(UnitType::Tank)) {
    }
    std::string getType() const override { return "Tank"; }
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Tank>(*this); }
};