#pragma once

class Unit;

class IInteractionStrategy {
public:
	virtual ~IInteractionStrategy() = default;
	virtual void apply(Unit& unit) = 0;
};