#pragma once
#include "neutral/NeutralObject.h"
#include "neutral/strategies/ResourceStrategy.h"

class TreasureChest : public NeutralObject {
public:
	explicit TreasureChest(std::shared_ptr<ILogger> logger) : NeutralObject(std::make_shared<ResourceStrategy>(logger), logger) {}
};