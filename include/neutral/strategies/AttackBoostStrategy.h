#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class AttackBoostStrategy : public IInteractionStrategy {
private:
	std::shared_ptr<ILogger> logger_;
public:
	explicit AttackBoostStrategy(std::shared_ptr<ILogger> logger) : logger_(logger) {}

	void apply(Unit& unit) override {
		unit.boostAttack(10);
		if (logger_) {
			logger_->log(LogEvent("INFO", "ENV", "Attack boosted by 10 for " + unit.getType()));
		}
	}
};