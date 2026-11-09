#pragma once
#include <stdexcept>

class Mana {
private:
	int mp;
	int maxMp;
public:
	Mana(int max) : maxMp(max), mp(max) {
		if (max <= 0) throw std::invalid_argument("Max MP must be positive");
	}

	void decrease(int amount) {
		mp -= amount;
		if (mp < 0) mp = 0;
	}

	void increase(int amount) {
		mp += amount;
		if (mp > maxMp) mp = maxMp;
	}

	bool isZero() const { return mp == 0; }
	int getValue() const { return mp; }
	int getMax() const { return maxMp; }
};