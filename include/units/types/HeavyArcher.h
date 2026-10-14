#pragma once
#include "units/Archer.h"

class HeavyArcher : public Archer {
public:
	HeavyArcher() : Archer(90, 10, 25, 'h') {}

	std::string getType() const override { return "HeavyArcher"; }

	std::unique_ptr<Unit> clone() const override { return std::unique_ptr<Unit>(new HeavyArcher(*this)); }
};