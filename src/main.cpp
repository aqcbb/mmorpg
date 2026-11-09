#include <iostream>
#include <cassert>
#include "base/Base.h"
#include "units/Unit.h"
#include "core/UnitTypeInfo.h"
#include "terrain/TerrainMap.h"
#include "terrain/types/Forest.h"
#include "terrain/types/Mountains.h"

int main() {
	auto base = std::make_shared<Base>(100, 10, 5);

	auto infantry = base->createUnit(UnitType::Infantry, 5, 5);
	assert(infantry != nullptr);
	assert(base->getUnitCount() == 1);
	std::cout << "Infantry id = " << infantry->getId() << "\n";

	auto info = UnitTypeInfo::getInfo(UnitType::Infantry);
	std::cout << "Infantry maxHealth = " << info->maxHealth << "\n";
	assert(info->maxHealth == 100);

	std::cout << "\nKilling infantry\n";
	infantry->takeDamage(1000);

	assert(base->getUnitCount() == 0);
	std::cout << "Base unit count after death = " << base->getUnitCount() << "\n";

	std::cout << "\nTesting TerrainProxy\n";
	auto mountains = std::make_shared<Mountains>();
	auto proxy = std::make_shared<TerrainProxy>(mountains);

	bool infantryCanPass = proxy->isPassable(UnitType::Infantry);
	bool flyingCanPass = proxy->isPassable(UnitType::FlyingUnit);

	std::cout << "Infantry passes mountains: " << (infantryCanPass ? "yes" : "no") << "\n";
	std::cout << "Flying passes mountains:   " << (flyingCanPass ? "yes" : "no") << "\n";

	assert(!infantryCanPass);
	assert(flyingCanPass);

	return 0;
}