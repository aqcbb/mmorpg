#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include "../units/Unit.h"

class GameField {
public:
	class Iterator;
private:
	int width;
	int height;
	int maxUnits;
	int unitCount;

	std::vector<std::vector<std::unique_ptr<Unit>>> grid;

	bool inBounds(int x, int y) const;
	bool isBorder(int x, int y) const;

public:
	GameField(int width, int height, int maxUnits);
	~GameField() {}

	GameField(const GameField& other);
	GameField& operator=(const GameField& other);

	GameField(GameField&& other) noexcept;
	GameField& operator=(GameField&& other) noexcept;

	bool addUnit(std::unique_ptr<Unit> unit, int x, int y);
	bool removeUnit(int x, int y);
	bool removeUnit(int index);
	Unit* getUnit(int x, int y) const;
	int size() const { return unitCount; }
	bool empty() const { return unitCount == 0; }
	void clear();

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getMaxUnits() const { return maxUnits; }

	void draw(std::ostream& os) const;

	Iterator begin();
	Iterator end();
};