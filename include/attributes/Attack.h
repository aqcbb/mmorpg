#pragma once
#include "Armor.h"

class Attack {
private:
	int damage;
public:
	explicit Attack(int dmg) : damage(dmg) {}

	int getDamage() const { return damage; }

	int calculateDamage(const Armor& targetArmor) const {
		int dmg = damage;
		targetArmor.reduceDamage(dmg);
		return dmg;
	}

	void increase(int value) { damage += value; }
};