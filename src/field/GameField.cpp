#include "field/GameField.h"
#include "field/GameFieldIterator.h"
#include <stdexcept>

bool GameField::inBounds(int x, int y) const {
	return x >= 0 && x < width && y >= 0 && y < height;
}

bool GameField::isBorder(int x, int y) const {
	return x == 0 || y == 0 || x == width - 1 || y == height - 1;
}

GameField::GameField(int w, int h, int maxU) : width(w), height(h), maxUnits(maxU), unitCount(0) {
	if (w < 3 || h < 3) throw std::invalid_argument("Field must be at least 3x3");
	if (maxU <= 0) throw std::invalid_argument("maxUnits must be positive");

	grid.resize(height);
	for (int y = 0; y < height; ++y) {
		grid[y].resize(width);
	}
}

GameField::GameField(const GameField& other)
	: width(other.width),
	height(other.height),
	maxUnits(other.maxUnits),
	unitCount(0)
{
	grid.resize(height);
	for (int y = 0; y < height; ++y) {
		grid[y].resize(width);
		for (int x = 0; x < width; ++x) {
			if (other.grid[y][x]) {
				grid[y][x] = other.grid[y][x]->clone();
				++unitCount;
			}
		}
	}
}

GameField& GameField::operator=(const GameField& other) {
	if (this == &other) return *this;

	width = other.width;
	height = other.height;
	maxUnits = other.maxUnits;
	unitCount = 0;

	grid.clear();
	grid.resize(height);
	for (int y = 0; y < height; ++y) {
		grid[y].resize(width);
		for (int x = 0; x < width; ++x) {
			if (other.grid[y][x]) {
				grid[y][x] = other.grid[y][x]->clone();
				++unitCount;
			}
		}
	}
	return *this;
}

GameField::GameField(GameField&& other) noexcept
	: width(other.width),
	height(other.height),
	maxUnits(other.maxUnits),
	unitCount(other.unitCount),
	grid(std::move(other.grid))
{
	other.width = 0;
	other.height = 0;
	other.maxUnits = 0;
	other.unitCount = 0;
}

GameField& GameField::operator=(GameField&& other) noexcept {
	if (this == &other) return *this;

	width = other.width;
	height = other.height;
	maxUnits = other.maxUnits;
	unitCount = other.unitCount;
	grid = std::move(other.grid);

	other.width = 0;
	other.height = 0;
	other.maxUnits = 0;
	other.unitCount = 0;

	return *this;
}

bool GameField::addUnit(std::unique_ptr<Unit> unit, int x, int y) {
	if (!unit) return false;
	if (!inBounds(x, y)) return false;
	if (isBorder(x, y)) return false;
	if (grid[y][x] != nullptr) return false;
	if (unitCount >= maxUnits) return false;

	unit->move(x, y);
	grid[y][x] = std::move(unit);
	++unitCount;
	return true;
}

bool GameField::removeUnit(int x, int y) {
	if (!inBounds(x, y)) return false;
	if (!grid[y][x]) return false;

	grid[y][x].reset();
	--unitCount;
	return true;
}

bool GameField::removeUnit(int index) {
	if (index < 0 || index >= unitCount) return false;

	int count = 0;
	for (int y = 1; y < height - 1; ++y) {
		for (int x = 1; x < width; ++x) {
			if (grid[y][x]) {
				if (count == index) {
					grid[y][x].reset();
					--unitCount;
					return true;
				}
				++count;
			}
		}
	}
	return false;
}

Unit* GameField::getUnit(int x, int y) const {
	if (!inBounds(x, y)) return nullptr;
	return grid[y][x].get();
}

void GameField::clear() {
	for (auto& row : grid) {
		for (auto& cell : row) {
			cell.reset();
		}
	}
	unitCount = 0;
}

void GameField::draw(std::ostream& os) const {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (isBorder(x, y)) {
				os << 'X';
			}
			else if (grid[y][x]) {
				os << grid[y][x]->getSymbol();
			}
			else {
				os << ' ';
			}
		}
		os << '\n';
	}
}

GameField::Iterator GameField::begin() {
	return Iterator(this, 1, 1);
}

GameField::Iterator GameField::end() {
	return Iterator(this, width - 1, height - 1);
}