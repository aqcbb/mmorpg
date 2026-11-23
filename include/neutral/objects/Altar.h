#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/AttackBoostStrategy.h"
#include "neutral/strategies/ManaBoostStrategy.h"
#include "core/UnitType.h"
#include <iostream>

class Altar : public NeutralObject {
public:
	explicit Altar(std::shared_ptr<ILogger> logger) : NeutralObject(nullptr, logger) {}

	char getSymbol() const override { return 'A'; }

	void interact(Unit& unit) override {
		if (unit.getInfo()->type == UnitType::Infantry || unit.getInfo()->type == UnitType::Archer) {
			strategy_ = std::make_shared<AttackBoostStrategy>(logger_);
		}
		else if (unit.getInfo()->type == UnitType::Mage) {
			strategy_ = std::make_shared<ManaBoostStrategy>(logger_);
		}
		else {
			strategy_ = std::make_shared<AttackBoostStrategy>(logger_);
		}
		strategy_->apply(unit);

		if (logger_) {
			logger_->log(LogEvent("INFO", "ENV", "Altar activated by Unit ID=" + std::to_string(unit.getId())));
		}
	}
};