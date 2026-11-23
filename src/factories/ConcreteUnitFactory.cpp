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
		case UnitType::Infantry: return std::make_unique<Infantry>(id, logger_);
		case UnitType::Archer: return std::make_unique<Archer>(id, logger_);
		case UnitType::Mage: return std::make_unique<Mage>(id, logger_);
		case UnitType::FlyingUnit: return std::make_unique<FlyingUnit>(id, logger_);
		case UnitType::Scout:      return std::make_unique<Scout>(id, logger_);
		case UnitType::Tank:       return std::make_unique<Tank>(id, logger_);
		case UnitType::Worker:     return std::make_unique<Worker>(id, logger_);
		case UnitType::Medic:      return std::make_unique<Medic>(id, logger_);
	}
	throw std::runtime_error("Unknown UnitType in ConcreteUnitFactory");
}