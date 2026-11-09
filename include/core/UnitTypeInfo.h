#pragma once

#include "UnitType.h"
#include <memory>
#include <unordered_map>

class UnitTypeInfo {
public:
	const int maxHealth;
	const int baseAttack;
	const double baseSpeed;
	const int cost;
	const UnitType type;

	UnitTypeInfo(UnitType type, int maxHealth, int baseAttack, double baseSpeed, int cost);

	static std::shared_ptr<UnitTypeInfo> getInfo(UnitType type);

private:
	static std::unordered_map<UnitType, std::shared_ptr<UnitTypeInfo>> registry;
	static std::unordered_map<UnitType, std::shared_ptr<UnitTypeInfo>> createRegistry();
};