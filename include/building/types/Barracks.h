#pragma once
#include "building/Building.h"
class Barracks : public Building {
public:
    Barracks(int id, int x, int y) : Building(id, "Barracks", 300, 'K', x, y) {}
};