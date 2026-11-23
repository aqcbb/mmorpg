#pragma once
#include <string>
#include <ostream>
#include <memory>
#include <vector>
#include "attributes/Armor.h"
#include "attributes/Attack.h"
#include "attributes/Health.h"
#include "attributes/Mana.h"
#include "core/Position.h"
#include "core/UnitTypeInfo.h"
#include "core/Resources.h"
#include "observer/IObservable.h"
#include "logging/ILogger.h"

class Unit : public IObservable {
protected:
    Health health;
    Armor armor;
    Attack attack;
    Mana mana;
    Resources inventory_;
    Point position;
    char symbol;
    int id_;
    std::string currentOrder_;
    std::shared_ptr<UnitTypeInfo> info_;
    std::vector<std::weak_ptr<IObserver>> observers_;
    std::shared_ptr<ILogger> logger_;

public:
    Unit(int hp, int arm, int dmg, int manaAmount, char sym, int id, std::shared_ptr<UnitTypeInfo> info, std::shared_ptr<ILogger> logger);
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
    int getArmorValue() const;
    int getDamageValue() const;

    void setOrder(const std::string& order) { currentOrder_ = order; }
    std::string getOrder() const { return currentOrder_; }

    void heal(int amount);
    void boostAttack(int amount);
    void boostMana(int amount);
    int getMana() const;

    void addResources(const Resources& res);
    Resources getInventory() const;
    void clearInventory();
};

inline std::ostream& operator<<(std::ostream& os, const Unit& unit) {
    os << "Unit [ID=" << unit.getId()
        << ", Type=" << unit.getType()
        << ", HP=" << unit.getHealth()
        << ", Pos=(" << unit.getPosition().x << "," << unit.getPosition().y << ")]";
    return os;
}