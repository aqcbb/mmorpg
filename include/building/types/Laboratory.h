#pragma once
#include "building/Building.h"
class Laboratory : public Building {
public:
    Laboratory(int id, int x, int y) : Building(id, "Laboratory", 150, 'L', x, y) {}
};