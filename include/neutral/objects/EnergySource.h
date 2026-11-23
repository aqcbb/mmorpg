#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/HealthRestoreStrategy.h"

class EnergySource : public NeutralObject {
public:
	explicit EnergySource(std::shared_ptr<ILogger> logger) : NeutralObject(std::make_shared<HealthRestoreStrategy>(logger), logger) {}

	char getSymbol() const override { return 'E'; }
};