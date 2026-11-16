#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class ResourceStrategy : public IInteractionStrategy {
public:
	void apply(Unit& unit) override {
		Resources loot(50, 20, 10);
		unit.addResources(loot);
		std::cout << "[Strategy] Unit " << unit.getId() << " collected: ";
		loot.print();
		std::cout << "\n";
	}
};