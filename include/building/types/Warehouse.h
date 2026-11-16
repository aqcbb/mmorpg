#pragma once
#include "building/Building.h"
class Warehouse : public Building {
public:
    Warehouse(int id, int x, int y) : Building(id, "Warehouse", 250, 'W', x, y) {}
};