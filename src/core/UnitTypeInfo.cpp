#include "core/UnitTypeInfo.h"
#include <stdexcept>

std::unordered_map<UnitType, std::shared_ptr<UnitTypeInfo>> UnitTypeInfo::registry = UnitTypeInfo::createRegistry();

UnitTypeInfo::UnitTypeInfo(UnitType type, int maxHealth, int baseAttack, double baseSpeed, int cost)
	: type(type), maxHealth(maxHealth), baseAttack(baseAttack), baseSpeed(baseSpeed), cost(cost) {}

std::unordered_map<UnitType, std::shared_ptr<UnitTypeInfo>> UnitTypeInfo::createRegistry() {
	std::unordered_map<UnitType, std::shared_ptr<UnitTypeInfo>> reg;

	reg[UnitType::Infantry] = std::make_shared<UnitTypeInfo>(UnitType::Infantry, 100, 20, 1.0, 50);

	reg[UnitType::Archer] = std::make_shared<UnitTypeInfo>(UnitType::Archer, 80, 25, 1.2, 60);

	reg[UnitType::Mage] = std::make_shared<UnitTypeInfo>(UnitType::Mage, 60, 30, 0.9, 80);

	reg[UnitType::FlyingUnit] = std::make_shared<UnitTypeInfo>(UnitType::FlyingUnit, 70, 15, 1.5, 70);

	return reg;
}

std::shared_ptr<UnitTypeInfo> UnitTypeInfo::getInfo(UnitType type) {
	auto it = registry.find(type);
	if (it == registry.end()) {
		throw std::runtime_error("Unknown UnitType in registry");
	}
	return it->second;
}