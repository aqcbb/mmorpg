#pragma once
#include "resource/ResourceSystem.h"
#include <iostream>

void ResourceSystem::addResources(const Resources& res) {
    storage_ = storage_ + res;
}

bool ResourceSystem::spendResources(const Resources& cost) {
    if (storage_.hasEnough(cost)) {
        storage_ = storage_ - cost;
        return true;
    }
    return false;
}

Resources ResourceSystem::getResources() const {
    return storage_;
}

void ResourceSystem::printResources() const {
    std::cout << "[Base Resources]\n";
    storage_.print();
    std::cout << "\n";
}