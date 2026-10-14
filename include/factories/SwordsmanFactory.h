#pragma once
#include "UnitFactory.h"
#include "../units/types/Swordsman.h"

class SwordsmanFactory : public UnitFactory {
public:
	std::unique_ptr<Unit> createUnit() const override {
		return std::unique_ptr<Unit>(new Swordsman());
	}
};