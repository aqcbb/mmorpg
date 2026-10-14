#pragma once
#include "UnitFactory.h"
#include "../units/types/Spearman.h"

class SpearmanFactory : public UnitFactory {
public:
	std::unique_ptr<Unit> createUnit() const override {
		return std::unique_ptr<Unit>(new Spearman());
	}
};