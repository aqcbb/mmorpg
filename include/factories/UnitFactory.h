#pragma once
#include <memory>
#include "units/Unit.h"

class UnitFactory {
public:
	virtual ~UnitFactory() = default;

	virtual std::unique_ptr<Unit> createUnit() const = 0;
};