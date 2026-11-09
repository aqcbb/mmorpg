#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/DamageStrategy.h"

class Trap : public NeutralObject {
public:
	Trap() : NeutralObject(std::make_shared<DamageStrategy>()) {}
};