#include "combat/CombatSystem.h"
#include "units/Unit.h"

int CombatSystem::calculateDamage(Unit& attacker, Unit& target) {
    int attackDmg = attacker.getDamageValue();
    int targetArmor = target.getArmorValue();

    int finalDmg = std::max(1, attackDmg - targetArmor);
    return finalDmg;
}

void CombatSystem::resolveCombat(Unit& attacker, Unit& target) {
    int dmg = calculateDamage(attacker, target);
    if (logger_) {
        logger_->log(LogEvent("INFO", "COMBAT", "Unit " + std::to_string(attacker.getId()) + " deals " + std::to_string(dmg) + " damage"));
    }
    target.takeDamage(dmg);
}