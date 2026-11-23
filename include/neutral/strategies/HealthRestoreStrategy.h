#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class HealthRestoreStrategy : public IInteractionStrategy {
private:
	std::shared_ptr<ILogger> logger_;
public:
	explicit HealthRestoreStrategy(std::shared_ptr<ILogger> logger) : logger_(logger) {}

	void apply(Unit& unit) override {
		unit.heal(50);
		if (logger_) {
			logger_->log(LogEvent("INFO", "ENV", "Health restored by 50 for " + unit.getType()));
		}
	}
};