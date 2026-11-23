#pragma once
#include "neutral/IInteractionStrategy.h"
#include "units/Unit.h"
#include <iostream>

class ResourceStrategy : public IInteractionStrategy {
private:
	std::shared_ptr<ILogger> logger_;
public:
	explicit ResourceStrategy(std::shared_ptr<ILogger> logger) : logger_(logger) {}

	void apply(Unit& unit) override {
		Resources loot(50, 20, 10);
		unit.addResources(loot);
		if (logger_) {
			logger_->log(LogEvent("INFO", "ENV", "Unit " + std::to_string(unit.getId()) + " collected 50 wood, 20 metal, 10 energy"));
		}
	}
};