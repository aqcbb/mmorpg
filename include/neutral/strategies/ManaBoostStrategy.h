#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class ManaBoostStrategy : public IInteractionStrategy {
public:
	void apply(Unit& unit) override {
		unit.boostMana(50);
		std::cout << "[Strategy] Mana boosted by 50 for " << unit.getType() << " (Current Mana: " << unit.getMana() << ")\n";
	}
};