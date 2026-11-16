#pragma once
#include "building/Building.h"
class PowerPlant : public Building {
public:
    PowerPlant(int id, int x, int y) : Building(id, "PowerPlant", 200, 'E', x, y) {}
};