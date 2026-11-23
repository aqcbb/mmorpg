#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/DamageStrategy.h"

class Trap : public NeutralObject {
public:
	explicit Trap(std::shared_ptr<ILogger> logger)
		: NeutralObject(std::make_shared<DamageStrategy>(logger), logger) {
	}
};