#pragma once
#include "UnitFactory.h"
#include "../units/types/LightArcher.h"

class LightArcherFactory : public UnitFactory {
public:
	std::unique_ptr<Unit> createUnit() const override {
		return std::unique_ptr<Unit>(new LightArcher());
	}
};