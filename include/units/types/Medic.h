#pragma once
#include "units/Unit.h"

class Medic : public Unit {
public:
    explicit Medic(int id, std::shared_ptr<ILogger> logger)
        : Unit(60, 2, 5, 0, 'm', id, UnitTypeInfo::getInfo(UnitType::Medic), logger) {
    }
    std::string getType() const override { return "Medic"; }
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Medic>(*this); }
};