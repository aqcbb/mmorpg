#include <iostream>
#include <cassert>
#include "base/Base.h"
#include "units/Unit.h"
#include "core/UnitTypeInfo.h"
#include "terrain/TerrainMap.h"
#include "terrain/types/Forest.h"
#include "terrain/types/Mountains.h"
#include "neutral/operators.h"
#include "neutral/objects/TreasureChest.h"
#include "neutral/objects/Trap.h"
#include "neutral/objects/Altar.h"
#include "neutral/objects/EnergySource.h"
#include "units/types/Mage.h"

int main() {
	std::cout << "Test: Observer + Proxy\n";

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

	std::cout << "\nTest: Strategy & Neutral Objects\n";

	auto mage = std::make_shared<Mage>(100);
	auto infantry2 = base->createUnit(UnitType::Infantry, 1, 1);

	std::cout << "\nTrap\n";
	std::cout << "Mage health before trap: " << mage->getHealth() << "\n";

	Trap trap;
	*mage - trap;

	std::cout << "Mage health after trap: " << mage->getHealth() << "\n";

	std::cout << "\nAltar\n";
	Altar altar;
	std::cout << "Infantry attack before altar: " << infantry2->getAttack() << "\n";
	*infantry2 * altar;
	std::cout << "Infantry attack after altar: " << infantry2->getAttack() << "\n\n";
	*mage* altar;

	std::cout << "\nChest\n";
	TreasureChest chest;
	*infantry2 + chest;

	std::cout << "\nSource\n";

	EnergySource source;
	*mage / source;
	std::cout << "Mage health after source: " << mage->getHealth() << "\n";
	return 0;
}