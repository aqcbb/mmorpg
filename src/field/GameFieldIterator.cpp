#include "field/GameFieldIterator.h"

GameField::Iterator::Iterator(GameField* f, int startX, int startY) : field(f), x(startX), y(startY) 
{
	skipEmpty();
}

void GameField::Iterator::skipEmpty() {
	if (!field) return;
	while (y < field->getHeight() - 1) {
		while (x < field->getWidth() - 1) {
			if (field->getUnit(x, y) != nullptr) {
				return;
			}
			++x;
		}
		x = 1;
		++y;
	}
	x = field->getWidth() - 1;
	y = field->getHeight() - 1;
}

Unit* GameField::Iterator::operator*() const {
	return field->getUnit(x, y);
}

GameField::Iterator& GameField::Iterator::operator++() {
	++x;
	skipEmpty();
	return *this;
}

bool GameField::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}

bool GameField::Iterator::operator==(const Iterator& other) const {
	return field == other.field && x == other.x && y == other.y;
}