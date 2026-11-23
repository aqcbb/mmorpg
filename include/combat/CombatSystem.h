#pragma once
#include "logging/ILogger.h"

class Unit;

class CombatSystem {
private:
    std::shared_ptr<ILogger> logger_;
public:
    CombatSystem(std::shared_ptr<ILogger> logger) : logger_(logger) {}
    int calculateDamage(Unit& attacker, Unit& target);
    void resolveCombat(Unit& attacker, Unit& target);
};