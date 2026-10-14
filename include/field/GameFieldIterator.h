#pragma once
#include "GameField.h"

class GameField::Iterator {
private:
	GameField* field;
	int x, y;

	void skipEmpty();
public:
	Iterator(GameField* f, int startX, int startY);

	Unit* operator*() const;
	Iterator& operator++();
	bool operator!=(const Iterator& other) const;
	bool operator==(const Iterator& other) const;
};