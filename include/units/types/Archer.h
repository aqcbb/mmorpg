#pragma once
#include "units/Unit.h"

class Archer : public Unit {
public:
	explicit Archer(int id, std::shared_ptr<ILogger> logger) : Unit(80, 5, 25, 0, 'A', id, UnitTypeInfo::getInfo(UnitType::Archer), logger) {}

	std::string getType() const override { return "Archer"; }
	std::unique_ptr<Unit> clone() const override {
		return std::unique_ptr<Unit>(new Archer(*this));
	}
};