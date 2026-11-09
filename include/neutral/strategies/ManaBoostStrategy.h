#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include "units/types/Infantry.h"
#include <iostream>

class ManaBoostStrategy : public IInteractionStrategy {
public:
	void apply(Unit& unit) override {
		std::cout << "[Strategy] Mana boosted by 50 for " << unit.getType() << "\n";
	}
};