#pragma once

#include "observer/IObserver.h"
#include "core/UnitType.h"
#include <memory>
#include <vector>

class Unit;

class Base : public IObserver, public std::enable_shared_from_this<Base> {
private:
	int health_;
	int maxUnits_;
	int defenseLevel_;
	int resources_;
	int nextUnitId_;
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
	std::shared_ptr<Unit> getUnitById(int id) const {
		for (const auto& u : units_) {
			if (u->getId() == id) return u;
		}
		return nullptr;
	}
	size_t getUnitCount() const { return units_.size(); }
};