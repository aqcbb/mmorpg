#pragma once
#include "units/Unit.h"

class Mage : public Unit {
public:
	explicit Mage(int id = 0) : Unit(60, 5, 30, 'M', id, UnitTypeInfo::getInfo(UnitType::Mage)) {}

	std::string getType() const override { return "Mage"; }
	std::unique_ptr<Unit> clone() const override {
		return std::unique_ptr<Unit>(new Mage(*this));
	}
};