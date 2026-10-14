#pragma once
#include "units/Archer.h"

class LightArcher : public Archer {
public:
	LightArcher() : Archer(70, 5, 30, 'l') {}

	std::string getType() const override { return "LightArcher"; }

	std::unique_ptr<Unit> clone() const override { return std::unique_ptr<Unit>(new LightArcher(*this)); }
};