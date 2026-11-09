#pragma once

#include "core/Position.h"
#include <chrono>
#include <string>

enum class UnitEventType {
	Created,
	Damaged,
	Destroyed
};

struct UnitEvent {
	UnitEventType type;
	int unitId;
	int damage;
	std::chrono::system_clock::time_point timestamp;
};