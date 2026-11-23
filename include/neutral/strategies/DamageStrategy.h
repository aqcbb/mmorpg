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
		unit.takeDamage(30);
		if (logger_) {
			logger_->log(LogEvent("INFO", "ENV", "Unit " + std::to_string(unit.getId()) + " took 30 damage from trap"));
		}
	}
};