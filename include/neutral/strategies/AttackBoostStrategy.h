#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include "units/types/Infantry.h"
#include <iostream>

class AttackBoostStrategy : public IInteractionStrategy {
public:
	void apply(Unit& unit) override {
		unit.boostAttack(10);
		std::cout << "[Strategy] Attack boosted by 10 for " << unit.getType() << "\n";
	}
};