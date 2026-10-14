#pragma once

class Armor {
private:
	int value	;
public:
	explicit Armor(int val) : value(val) {}

	int getValue() const { return value; }

	void reduceDamage(int& damage) const {
		damage -= value;
		if (damage < 0) damage = 0;
	}
};