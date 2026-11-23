#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class ManaBoostStrategy : public IInteractionStrategy {
private:
	std::shared_ptr<ILogger> logger_;
public:
	explicit ManaBoostStrategy(std::shared_ptr<ILogger> logger) : logger_(logger) {}

	void apply(Unit& unit) override {
		unit.boostMana(50);
		if (logger_) {
			logger_->log(LogEvent("INFO", "ENV", "Mana boosted by 50 for " + unit.getType()));
		}
	}
};