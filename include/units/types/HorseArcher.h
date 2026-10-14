#pragma once
#include "units/Cavalry.h"

class HorseArcher : public Cavalry {
public:
	HorseArcher() : Cavalry(100, 10, 28, 'H') {}

	std::string getType() const override { return "HorseArcher"; }

	std::unique_ptr<Unit> clone() const override { return std::unique_ptr<Unit>(new HorseArcher(*this)); }
};