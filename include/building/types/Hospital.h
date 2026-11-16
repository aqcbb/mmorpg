#pragma once
#include "building/Building.h"
class Hospital : public Building {
public:
    Hospital(int id, int x, int y) : Building(id, "Hospital", 200, 'H', x, y) {}
};