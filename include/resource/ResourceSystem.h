#pragma once
#include "core/Resources.h"

class ResourceSystem {
private:
    Resources storage_;
public:
    ResourceSystem() = default;
    void addResources(const Resources& res);
    bool spendResources(const Resources& cost);
    Resources getResources() const;
    void printResources() const;
};