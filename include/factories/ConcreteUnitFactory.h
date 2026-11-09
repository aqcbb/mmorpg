#pragma once
#include "UnitFactory.h"
#include "core/UnitType.h"

class ConcreteUnitFactory : public UnitFactory {
private:
	UnitType type_;
public:
	explicit ConcreteUnitFactory(UnitType type) : type_(type) {}

	std::unique_ptr<Unit> createUnit() const override;
	std::unique_ptr<Unit> createUnit(int id) const;
};