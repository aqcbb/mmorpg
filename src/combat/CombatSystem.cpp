#include "combat/CombatSystem.h"
#include "units/Unit.h"

int CombatSystem::calculateDamage(Unit& attacker, Unit& target) {
    return 0;
}

void CombatSystem::resolveCombat(Unit& attacker, Unit& target) {
    int dmg = calculateDamage(attacker, target);
    target.takeDamage(dmg);
}