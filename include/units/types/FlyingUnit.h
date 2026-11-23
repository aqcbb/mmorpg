#pragma once
#include "units/Unit.h"

class FlyingUnit : public Unit {
public:
	explicit FlyingUnit(int id, std::shared_ptr<ILogger> logger) : Unit(70, 5, 15, 0, 'F', id, UnitTypeInfo::getInfo(UnitType::FlyingUnit), logger) {}

	std::string getType() const override { return "FlyingUnit"; }
	std::unique_ptr<Unit> clone() const override {
		return std::unique_ptr<Unit>(new FlyingUnit(*this));	
	}
};