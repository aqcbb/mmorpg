#pragma once
#include "units/Unit.h"

class Medic : public Unit {
public:
    explicit Medic(int id = 0)
        : Unit(60, 2, 5, 0, 'm', id, UnitTypeInfo::getInfo(UnitType::Medic)) {
    }
    std::string getType() const override { return "Medic"; }
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Medic>(*this); }
};