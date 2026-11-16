#include "building/Building.h"

Building::Building(int id, std::string type, int hp, char sym, int x, int y)
    : id_(id), type_(std::move(type)), health_(hp), maxHealth_(hp),
    symbol_(sym), x_(x), y_(y), buildProgress_(0) {
}

void Building::update() {
    if (buildProgress_ < 100) buildProgress_ += 25;
}

void Building::produce() {}