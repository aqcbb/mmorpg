#pragma once
#include "UnitFactory.h"
#include "core/UnitType.h"
#include "logging/ILogger.h"

class ConcreteUnitFactory : public UnitFactory {
private:
	UnitType type_;
	std::shared_ptr<ILogger> logger_;
public:
	explicit ConcreteUnitFactory(UnitType type, std::shared_ptr<ILogger> logger) : type_(type), logger_(logger) {}

	std::unique_ptr<Unit> createUnit() const override;
	std::unique_ptr<Unit> createUnit(int id) const;
};