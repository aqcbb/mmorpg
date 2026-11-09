#pragma once
#include "units/Unit.h"

class Archer : public Unit {
public:
	explicit Archer(int id = 0) : Unit(80, 5, 25, 'A', id, UnitTypeInfo::getInfo(UnitType::Infantry)) {}

	std::string getType() const override { return "Archer"; }
	std::unique_ptr<Unit> clone() const override {
		return std::unique_ptr<Unit>(new Archer(*this));
	}
};