#pragma once

#include "UnitEvent.h"

class IObserver {
public:
	virtual ~IObserver() = default;
	virtual void onUnitEvent(const UnitEvent& event) = 0;
};