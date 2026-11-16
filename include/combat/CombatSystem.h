#pragma once

class Unit;

class CombatSystem {
public:
    int calculateDamage(Unit& attacker, Unit& target);
    void resolveCombat(Unit& attacker, Unit& target);
};