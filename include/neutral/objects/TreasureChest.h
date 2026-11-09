#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/ResourceStrategy.h"

class TreasureChest : public NeutralObject {
public:
	TreasureChest() : NeutralObject(std::make_shared<ResourceStrategy>()) {}
};