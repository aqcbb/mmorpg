#pragma once
#include "units/Cavalry.h"

class Cataphract : public Cavalry {
public:
	Cataphract() : Cavalry(150, 25, 35, 'C') {}

	std::string getType() const override { return "Cataphract"; }

	std::unique_ptr<Unit> clone() const override { return std::unique_ptr<Unit>(new Cataphract(*this)); }
};