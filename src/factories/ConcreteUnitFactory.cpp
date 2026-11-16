#include "factories/ConcreteUnitFactory.h"
#include "units/types/Infantry.h"
#include "units/types/Archer.h"
#include "units/types/Mage.h"
#include "units/types/FlyingUnit.h"
#include "units/types/Scout.h"
#include "units/types/Tank.h"
#include "units/types/Worker.h"
#include "units/types/Medic.h"
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
		case UnitType::Scout:      return std::make_unique<Scout>(id);
		case UnitType::Tank:       return std::make_unique<Tank>(id);
		case UnitType::Worker:     return std::make_unique<Worker>(id);
		case UnitType::Medic:      return std::make_unique<Medic>(id);
	}
	throw std::runtime_error("Unknown UnitType in ConcreteUnitFactory");
}