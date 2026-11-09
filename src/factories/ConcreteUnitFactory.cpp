#include "factories/ConcreteUnitFactory.h"
#include "units/types/Infantry.h"
#include "units/types/Archer.h"
#include "units/types/Mage.h"
#include "units/types/FlyingUnit.h"
#include <stdexcept>

std::unique_ptr<Unit> ConcreteUnitFactory::createUnit() const {
	return createUnit(0);
}

std::unique_ptr<Unit> ConcreteUnitFactory::createUnit(int id) const {
	switch (type_) {
		case UnitType::Infantry: return std::make_unique<Infantry>(id);
		case UnitType::Archer: return std::make_unique<Archer>(id);
		case UnitType::Mage: return std::make_unique<Mage>(id);
		case UnitType::FlyingUnit: return std::make_unique<FlyingUnit>(id);
	}
	throw std::runtime_error("Unknown UnitType in ConcreteUnitFactory");
}