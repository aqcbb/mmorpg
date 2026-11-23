#include "units/Unit.h"
#include <algorithm>
#include <chrono>
#include <iostream>

Unit::Unit(int hp, int arm, int dmg, int manaAmount, char sym, int id, std::shared_ptr<UnitTypeInfo> info, std::shared_ptr<ILogger> logger)
    : health(hp), armor(arm), attack(dmg), mana(manaAmount), symbol(sym), id_(id), info_(info), logger_(logger) {
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

    if (logger_) {
        std::string msg = "Unit " + getType() + "(ID=" + std::to_string(id_) + ") took " + std::to_string(finalDmg) + " damage. HP: " + std::to_string(health.getValue());
        logger_->log(LogEvent("INFO", "UNIT", msg));
    }

    notify({ UnitEventType::Damaged, id_, finalDmg, std::chrono::system_clock::now() });
    checkDeath(finalDmg);
}

void Unit::subscribe(std::shared_ptr<IObserver> observer) {
    observers_.push_back(observer);
}

void Unit::unsubscribe(std::shared_ptr<IObserver> observer) {
    observers_.erase(
        std::remove_if(observers_.begin(), observers_.end(),
            [&](const std::weak_ptr<IObserver>& wp) {
                auto sp = wp.lock();
                return !sp || sp == observer;
            }),
        observers_.end()
    );
}

void Unit::notify(const UnitEvent& event) {
    for (auto it = observers_.begin(); it != observers_.end(); ) {
        if (auto obs = it->lock()) {
            obs->onUnitEvent(event);
            ++it;
        }
        else {
            it = observers_.erase(it);
        }
    }
}

int Unit::getId() const { return id_; }
Point Unit::getPosition() const { return position; }
char Unit::getSymbol() const { return symbol; }
bool Unit::isAlive() const { return !health.isZero(); }
std::shared_ptr<UnitTypeInfo> Unit::getInfo() const { return info_; }
int Unit::getHealth() const { return health.getValue(); }
int Unit::getArmorValue() const { return armor.getValue(); }
int Unit::getDamageValue() const { return attack.getDamage(); }
int Unit::getMana() const { return mana.getValue(); }

void Unit::heal(int amount) { health.increase(amount); }
void Unit::boostAttack(int amount) { attack.increase(amount); }
void Unit::boostMana(int amount) { mana.increase(amount); }

void Unit::addResources(const Resources& res) {
    inventory_ = inventory_ + res;
}
Resources Unit::getInventory() const {
    return inventory_;
}
void Unit::clearInventory() {
    inventory_ = Resources(0, 0, 0);
}