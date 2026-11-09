#pragma once
#include "Unit.h"

class Infantry : public Unit {
public:
	explicit Infantry(int id = 0) : Unit(100, 15, 20, 'I', id, UnitTypeInfo::getInfo(UnitType::Infantry)) {}

	std::string getType() const override { return "Infantry"; }
	std::unique_ptr<Unit> clone() const override {
		return std::unique_ptr<Unit>(new Infantry(*this));
	}
};