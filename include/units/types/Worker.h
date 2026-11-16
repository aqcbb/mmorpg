#pragma once
#include "units/Unit.h"

class Worker : public Unit {
public:
    explicit Worker(int id = 0)
        : Unit(80, 2, 5, 0, 'w', id, UnitTypeInfo::getInfo(UnitType::Worker)) {
    }
    std::string getType() const override { return "Worker"; }
    std::unique_ptr<Unit> clone() const override { return std::make_unique<Worker>(*this); }
};