#pragma once

#include "observer/IObserver.h"
#include "core/Resources.h"
#include "core/UnitType.h"
#include <memory>
#include <vector>

class Unit;
class Building;

class Base : public IObserver, public std::enable_shared_from_this<Base> {
private:
	int health_;
	int maxUnits_;
	int defenseLevel_;
	Resources resources_;
	int nextUnitId_;
	int nextBuildingId_;
	std::vector<std::shared_ptr<Unit>> units_;
	std::vector<std::shared_ptr<Building>> buildings_;
public:
	Base(int health, int maxUnits, int defenseLevel);
	~Base() override = default;

	void onUnitEvent(const UnitEvent& event) override;

	std::shared_ptr<Unit> createUnit(UnitType type, int x, int y);
	void removeUnit(int unitId);

	void addBuilding(std::shared_ptr<Building> building);
	std::shared_ptr<Building> getBuildingById(int id) const;

	void addResources(const Resources& res);
	bool spendResources(const Resources& cost);
	Resources getResources() const { return resources_; }

	int getHealth() const { return health_; }
	int getMaxUnits() const { return maxUnits_; }
	int getDefenseLevel() const { return defenseLevel_; }
	std::shared_ptr<Unit> getUnitById(int id) const;
	size_t getUnitCount() const { return units_.size(); }
	size_t getBuildingCount() const { return buildings_.size(); }
};