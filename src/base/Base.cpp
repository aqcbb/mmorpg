#include "base/Base.h"
#include "units/Unit.h"
#include "factories/ConcreteUnitFactory.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

Base::Base(int health, int maxUnits, int defenseLevel) : health_(health), maxUnits_(maxUnits), defenseLevel_(defenseLevel), resources_(0), nextUnitId_(1) {}

void Base::onUnitEvent(const UnitEvent& event) {
	switch (event.type) {
	case UnitEventType::Created:
		std::cout << "[Base] Unit " << event.unitId << " created\n";
		break;

	case UnitEventType::Damaged:
		std::cout << "[Base] Unit " << event.unitId << " took " << event.damage << " damage\n";
		break;

	case UnitEventType::Destroyed:
		std::cout << "[Base] Unit " << event.unitId << " destroyed\n";
		units_.erase(std::remove_if(units_.begin(), units_.end(), [&](const std::shared_ptr<Unit>& u) {return u->getId() == event.unitId; }), units_.end());
		break;
	}
}

std::shared_ptr<Unit> Base::createUnit(UnitType type, int x, int y) {
	if (units_.size() >= static_cast<size_t>(maxUnits_)) {
		std::cerr << "[Base] Cannot create unit: max limit reached\n";
		return nullptr;
	}

	ConcreteUnitFactory factory(type);
	auto unit = factory.createUnit();
	
	std::shared_ptr<Unit> sharedUnit = std::move(unit);

	sharedUnit->subscribe(shared_from_this());
	sharedUnit->notify({ UnitEventType::Created, sharedUnit->getId(), 0,
						 std::chrono::system_clock::now() });
	units_.push_back(sharedUnit);
	return sharedUnit;
}

void Base::removeUnit(int unitId) {
	units_.erase(std::remove_if(units_.begin(), units_.end(), [unitId](const std::shared_ptr<Unit>& u) {return u->getId() == unitId; }), units_.end());
}