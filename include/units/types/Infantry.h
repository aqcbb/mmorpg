#pragma once
#include "units/Unit.h"

class Infantry : public Unit {
public:
	explicit Infantry(int id, std::shared_ptr<ILogger> logger) : Unit(100, 15, 20, 0, 'I', id, UnitTypeInfo::getInfo(UnitType::Infantry), logger) {}

	std::string getType() const override { return "Infantry"; }
	std::unique_ptr<Unit> clone() const override {
		return std::unique_ptr<Unit>(new Infantry(*this));
	}
};