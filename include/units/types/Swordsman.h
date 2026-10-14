#pragma once
#include "units/Infantry.h"

class Swordsman : public Infantry {
public:
	Swordsman() : Infantry(120, 15, 25, 'S') {}
	
	std::string getType() const override { return "Swordsman"; }

	std::unique_ptr<Unit> clone() const override { return std::unique_ptr<Unit>(new Swordsman(*this)); }
};