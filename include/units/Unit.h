#pragma once
#include <string>
#include <memory>
#include <vector>
#include "attributes/Armor.h"
#include "attributes/Attack.h"
#include "attributes/Health.h"
#include "attributes/Mana.h"
#include "core/Position.h"
#include "core/UnitTypeInfo.h"
#include "observer/IObservable.h"

class Unit : public IObservable {
protected:
    Health health;
    Armor armor;
    Attack attack;
    Mana mana;
    Point position;
    char symbol;
    int id_;
    std::shared_ptr<UnitTypeInfo> info_;
    std::vector<std::shared_ptr<IObserver>> observers_;

public:
    Unit(int hp, int arm, int dmg, int manaAmount, char sym, int id, std::shared_ptr<UnitTypeInfo> info);
    virtual ~Unit() = default;

    virtual std::string getType() const = 0;
    virtual std::unique_ptr<Unit> clone() const = 0;
    virtual void move(Point newPos);
    virtual void attackUnit(Unit& target);
    virtual void takeDamage(int dmg);
    void checkDeath(int dmg);

    void subscribe(std::shared_ptr<IObserver> observer) override;
    void unsubscribe(std::shared_ptr<IObserver> observer) override;
    void notify(const UnitEvent& event) override;

    int getId() const;
    Point getPosition() const;
    char getSymbol() const;
    bool isAlive() const;
    std::shared_ptr<UnitTypeInfo> getInfo() const;
    int getHealth() const;

    void heal(int amount);
    void boostAttack(int amount);
    void boostMana(int amount);
    int getMana() const;
};