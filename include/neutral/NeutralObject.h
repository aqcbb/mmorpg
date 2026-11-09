#pragma once

#include "IInteractionStrategy.h"
#include <memory>

class Unit;

class NeutralObject {
protected:
	std::shared_ptr<IInteractionStrategy> strategy_;
public:
	explicit NeutralObject(std::shared_ptr<IInteractionStrategy> strategy);
	virtual ~NeutralObject() = default;

	virtual void interact(Unit& unit) = 0;
};