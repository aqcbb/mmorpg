#pragma once
#include <string>
#include <memory>
#include "attributes/Armor.h"
#include "attributes/Attack.h"
#include "attributes/Health.h"

struct Point {
	int x = 0;
	int y = 0;
};

class Unit {
protected:
	Health health;
	Armor armor;
	Attack attack;
	Point position;
	char symbol;
public:
	Unit(int hp, int arm, int dmg, char sym) : health(hp), armor(arm), attack(dmg), symbol(sym) {}

	virtual ~Unit() = default;

	virtual std::string getType() const = 0;
	virtual std::unique_ptr<Unit> clone() const = 0;

	void move(int x, int y) { position = { x, y }; }
	Point getPosition() const { return position; }
	char getSymbol() const { return symbol; }
	bool isAlive() const { return !health.isZero(); }

	void takeDamage(int dmg) {
		int finalDmg = dmg;
		armor.reduceDamage(finalDmg);
		health.decrease(finalDmg);
	}
};