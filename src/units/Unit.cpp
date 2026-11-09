#include "units/Unit.h"
#include <algorithm>
#include <chrono>
#include <iostream>

Unit::Unit(int hp, int arm, int dmg, int manaAmount, char sym, int id, std::shared_ptr<UnitTypeInfo> info)
    : health(hp), armor(arm), attack(dmg), mana(manaAmount), symbol(sym), id_(id), info_(info) {
}

void Unit::move(Point newPos) {
    position = newPos;
}

void Unit::checkDeath(int dmg) {
    if (!isAlive()) {
        notify({ UnitEventType::Destroyed, id_, dmg, std::chrono::system_clock::now() });
    }
}

void Unit::attackUnit(Unit& target) {
    int dmg = attack.calculateDamage(target.armor);
    target.health.decrease(dmg);
    target.notify({ UnitEventType::Damaged, target.id_, dmg, std::chrono::system_clock::now() });
    target.checkDeath(dmg);
}

void Unit::takeDamage(int dmg) {
    int finalDmg = dmg;
    armor.reduceDamage(finalDmg);
    health.decrease(finalDmg);
    notify({ UnitEventType::Damaged, id_, finalDmg, std::chrono::system_clock::now() });
    checkDeath(finalDmg);
}

void Unit::subscribe(std::shared_ptr<IObserver> observer) {
    observers_.push_back(observer);
}

void Unit::unsubscribe(std::shared_ptr<IObserver> observer) {
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void Unit::notify(const UnitEvent& event) {
    for (auto& obs : observers_) obs->onUnitEvent(event);
}

int Unit::getId() const { return id_; }
Point Unit::getPosition() const { return position; }
char Unit::getSymbol() const { return symbol; }
bool Unit::isAlive() const { return !health.isZero(); }
std::shared_ptr<UnitTypeInfo> Unit::getInfo() const { return info_; }
int Unit::getHealth() const { return health.getValue(); }

void Unit::heal(int amount) { health.increase(amount); }
void Unit::boostAttack(int amount) { attack.increase(amount); }
void Unit::boostMana(int amount) { mana.increase(amount); }
int Unit::getMana() const { return mana.getValue(); }