#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class ResourceStrategy : public IInteractionStrategy {
public:
	void apply(Unit& unit) override {
		std::cout << "[Strategy] Unit " << unit.getId() << " collected resources (gold +50)\n";
	}
};