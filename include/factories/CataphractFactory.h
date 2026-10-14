#pragma once
#include "UnitFactory.h"
#include "../units/types/Cataphract.h"

class CataphractFactory : public UnitFactory {
public:
	std::unique_ptr<Unit> createUnit() const override {
		return std::unique_ptr<Unit>(new Cataphract());
	}
};