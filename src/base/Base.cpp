#include "base/Base.h"
#include "units/Unit.h"
#include "building/Building.h"
#include "factories/ConcreteUnitFactory.h"
#include "logging/LogEvent.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

Base::Base(int health, int maxUnits, int defenseLevel, std::shared_ptr<ILogger> logger) 
	: health_(health), maxUnits_(maxUnits), defenseLevel_(defenseLevel), resources_(0, 0, 0), nextUnitId_(1), nextBuildingId_(1), logger_(logger)
{}

void Base::onUnitEvent(const UnitEvent& event) {
	switch (event.type) {
	case UnitEventType::Created:
		break;

	case UnitEventType::Damaged:
		break;

	case UnitEventType::Destroyed:
		if (logger_) logger_->log(LogEvent("ALERT", "BASE", "Unit " + std::to_string(event.unitId) + " destroyed"));
		units_.erase(std::remove_if(units_.begin(), units_.end(),
			[&](const std::shared_ptr<Unit>& u) { return u->getId() == event.unitId; }), units_.end());
		break;
	}
}

std::shared_ptr<Unit> Base::createUnit(UnitType type, int x, int y) {
	if (units_.size() >= static_cast<size_t>(maxUnits_)) {
		if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Cannot create unit: max limit reached"));
		return nullptr;
	}

	ConcreteUnitFactory factory(type, logger_);
	auto unit = factory.createUnit(nextUnitId_++);

	std::shared_ptr<Unit> sharedUnit = std::move(unit);

	sharedUnit->move(Point{ x, y });

	sharedUnit->subscribe(shared_from_this());
	sharedUnit->notify({ UnitEventType::Created, sharedUnit->getId(), 0,
						 std::chrono::system_clock::now() });
	units_.push_back(sharedUnit);
	return sharedUnit;
}

void Base::removeUnit(int unitId) {
	units_.erase(std::remove_if(units_.begin(), units_.end(), [unitId](const std::shared_ptr<Unit>& u) {return u->getId() == unitId; }), units_.end());
}

std::shared_ptr<Unit> Base::getUnitById(int id) const {
	for (const auto& u : units_) {
		if (u->getId() == id) return u;
	}
	return nullptr;
}

void Base::addResources(const Resources& res) {
	resources_ = resources_ + res;

	if (logger_) {
		std::ostringstream oss;
		oss << "Resources received! Current: [Wood: " << resources_.getWood()
			<< ", Metal: " << resources_.getMetal()
			<< ", Energy: " << resources_.getEnergy() << "]";
		logger_->log(LogEvent("INFO", "BASE", oss.str()));
	}
}

bool Base::spendResources(const Resources& cost) {
	if (!resources_.hasEnough(cost)) {
		if (logger_) logger_->log(LogEvent("ERROR", "BASE", "Not enough resources!"));
		return false;
	}
	resources_ = resources_ - cost;
	return true;
}

void Base::addBuilding(std::shared_ptr<Building> building) {
	buildings_.push_back(building);
}

std::shared_ptr<Building> Base::getBuildingById(int id) const {
	for (const auto& b : buildings_) {
		if (b->getId() == id) return b;
	}
	return nullptr;
}	