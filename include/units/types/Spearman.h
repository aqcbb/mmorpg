#pragma once
#include "units/Infantry.h"

class Spearman : public Infantry {
public:
	Spearman() : Infantry(100, 10, 30, 'P') {}

	std::string getType() const override { return "Spearman"; }

	std::unique_ptr<Unit> clone() const override { return std::unique_ptr<Unit>(new Spearman(*this)); }
};