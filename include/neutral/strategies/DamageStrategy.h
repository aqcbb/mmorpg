#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include "units/types/Infantry.h"
#include <iostream>

class DamageStrategy : public IInteractionStrategy {
public:
	void apply(Unit& unit) override {
		unit.takeDamage(30);
		std::cout << "[Strategy] Unit " << unit.getId() << " took 30 damage from trap\n";
	}
};