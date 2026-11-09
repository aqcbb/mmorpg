#pragma once
#include "units/Unit.h"

class FlyingUnit : public Unit {
public:
	explicit FlyingUnit(int id = 0) : Unit(70, 5, 15, 'F', id, UnitTypeInfo::getInfo(UnitType::FlyingUnit)) {}

	std::string getType() const override { return "FlyingUnit"; }
	std::unique_ptr<Unit> clone() const override {
		return std::unique_ptr<Unit>(new FlyingUnit(*this));	
	}
};