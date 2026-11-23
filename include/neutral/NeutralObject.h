#pragma once

#include "IInteractionStrategy.h"
#include "logging/ILogger.h"
#include <memory>

class Unit;

class NeutralObject {
protected:
	std::shared_ptr<IInteractionStrategy> strategy_;
	std::shared_ptr<ILogger> logger_;
public:
	explicit NeutralObject(std::shared_ptr<IInteractionStrategy> strategy, std::shared_ptr<ILogger> logger) 
		: strategy_(std::move(strategy)), logger_(logger) {}
	virtual ~NeutralObject() = default;

	virtual void interact(Unit& unit) {
		if (strategy_) {
			strategy_->apply(unit);
		}
	}
};

inline std::ostream& operator<<(std::ostream& os, const NeutralObject& obj) {
	os << "NeutralObject";
	return os;
}