#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/HealthRestoreStrategy.h"

class EnergySource : public NeutralObject {
public:
	EnergySource() : NeutralObject(std::make_shared<HealthRestoreStrategy>()) {}
};