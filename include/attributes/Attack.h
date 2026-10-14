#pragma once

class Attack {
private:
	int damage;
public:
	explicit Attack(int dmg) : damage(dmg) {}

	int getDamage() const { return damage; }
};