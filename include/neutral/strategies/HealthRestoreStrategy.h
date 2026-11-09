#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include "units/types/Infantry.h"
#include <iostream>

class HealthRestoreStrategy : public IInteractionStrategy {
public:
	void apply(Unit& unit) override {
		unit.heal(50);
		std::cout << "[Strategy] Health restored by 50 for " << unit.getType() << "\n";
	}
};