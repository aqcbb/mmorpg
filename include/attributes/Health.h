#pragma once
#include <stdexcept>

class Health {
private:
	int hp;
	int maxHp;
public:
	Health(int max) : maxHp(max), hp(max) {
		if (max <= 0) throw std::invalid_argument("Max HP must be positive");
	}

	void decrease(int amount) {
		hp -= amount;
		if (hp < 0) hp = 0;
	}

	void increase(int amount) {
		hp += amount;
		if (hp > maxHp) hp = maxHp;
	}

	bool isZero() const { return hp == 0; }
	int getValue() const { return hp; }
	int getMax() const { return maxHp; }
};