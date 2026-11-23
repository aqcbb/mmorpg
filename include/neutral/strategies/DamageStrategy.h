#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class DamageStrategy : public IInteractionStrategy {
private:
	std::shared_ptr<ILogger> logger_;
public:
	explicit DamageStrategy(std::shared_ptr<ILogger> logger) : logger_(logger) {}

	void apply(Unit& unit) override {
		int actualDmg = unit.takeDamage(30);
		if (logger_) {
			logger_->log(LogEvent("INFO", "ENV", "Trap hit Unit " + std::to_string(unit.getId()) + " for " + std::to_string(actualDmg) + " damage (after armor)."));
		}
	}
};