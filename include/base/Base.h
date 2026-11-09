#pragma once

#include "observer/IObserver.h"
#include "core/UnitType.h"
#include <memory>
#include <vector>

class Unit;

class Base : public IObserver {
private:
	int health_;
	int maxUnits_;
	int defenseLevel_;
	int resources_;
	std::vector<std::shared_ptr<Unit>> units_;
public:
	Base(int health, int maxUnits, int defenseLevel);
	~Base() override = default;

	void onUnitEvent(const UnitEvent& event) override;

	std::shared_ptr<Unit> createUnit(UnitType type, int x, int y);
	void removeUnit(int unitId);

	int getHealth() const { return health_; }
	int getMaxUnits() const { return maxUnits_; }
	int getDefenseLevel() const { return defenseLevel_; }
	size_t getUnitCount() const { return units_.size(); }
};