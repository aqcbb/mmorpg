#pragma once
#include <iostream>
#include <algorithm>

class Resources {
private:
	int wood_;
	int metal_;
	int energy_;
public:
	Resources() : wood_(0), metal_(0), energy_(0) {}
	Resources(int w, int m, int e) : wood_(w), metal_(m), energy_(e) {}

	int getWood() const { return wood_; }
	int getMetal() const { return metal_; }
	int getEnergy() const { return energy_; }

	void setWood(int value) { wood_ = std::max(0, value); }
	void setMetal(int value) { metal_ = std::max(0, value); }
	void setEnergy(int value) { energy_ = std::max(0, value); }

	void addWood(int amount) { wood_ = std::max(0, wood_ + amount); }
	void addMetal(int amount) { metal_ = std::max(0, metal_ + amount); }
	void addEnergy(int amount) { energy_ = std::max(0, energy_ + amount); }

	Resources operator+(const Resources& other) const {
		return Resources(wood_ + other.wood_, metal_ + other.metal_, energy_ + other.energy_);
	}

	Resources operator-(const Resources& other) const {
		return Resources(
			std::max(0, wood_ - other.wood_),
			std::max(0, metal_ - other.metal_),
			std::max(0, energy_ - other.energy_)
		);
	}

	bool hasEnough(const Resources& cost) const {
		return wood_ >= cost.wood_ && metal_ >= cost.metal_ && energy_ >= cost.energy_;
	}

	void print() const {
		std::cout << "[Wood: " << wood_ << ", Metal: " << metal_ << ", Energy: " << energy_ << "]";
	}
};