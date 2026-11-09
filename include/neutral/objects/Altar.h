#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/AttackBoostStrategy.h"
#include "neutral/strategies/ManaBoostStrategy.h"
#include <iostream>

class Altar : public NeutralObject {
public:
	Altar() : NeutralObject(nullptr) {}

	void interact(Unit& unit) override {
		if (unit.getType() == "Infantry" || unit.getType() == "Archer") {
			strategy_ = std::make_shared<AttackBoostStrategy>();
		}
		else if (unit.getType() == "Mage") {
			strategy_ = std::make_shared<ManaBoostStrategy>();
		}
		else {
			strategy_ = std::make_shared<AttackBoostStrategy>();
		}
		strategy_->apply(unit);
	}
};