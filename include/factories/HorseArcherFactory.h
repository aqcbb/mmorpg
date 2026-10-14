#pragma once
#include "UnitFactory.h"
#include "../units/types/HorseArcher.h"

class HorseArcherFactory : public UnitFactory {
public:
	std::unique_ptr<Unit> createUnit() const override {
		return std::unique_ptr<Unit>(new HorseArcher());
	}
};