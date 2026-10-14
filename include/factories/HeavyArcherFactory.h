#pragma once
#include "UnitFactory.h"
#include "../units/types/HeavyArcher.h"

class HeavyArcherFactory : public UnitFactory {
public:
	std::unique_ptr<Unit> createUnit() const override {
		return std::unique_ptr<Unit>(new HeavyArcher());
	}
};