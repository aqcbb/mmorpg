#pragma once
#include <string>
#include <memory>
#include "attributes/Armor.h"
#include "attributes/Attack.h"
#include "attributes/Health.h"
#include "core/Position.h"
#include "core/UnitTypeInfo.h"
#include "observer/IObservable.h"

class Unit : public IObservable {
protected:
	Health health;
	Armor armor;
	Attack attack;
	Point position;
	char symbol;
	int id_;
	std::shared_ptr<UnitTypeInfo> info_;
	std::vector<std::shared_ptr<IObserver>> observers_;
public:
	Unit(int hp, int arm, int dmg, char sym, int id, std::shared_ptr<UnitTypeInfo> info) : health(hp), armor(arm), attack(dmg), symbol(sym), id_(id), info_(info) {}

	virtual ~Unit() = default;

	virtual std::string getType() const = 0;
	virtual std::unique_ptr<Unit> clone() const = 0;

	virtual void move(Point newPos) { position = newPos; }

	virtual void attackUnit(Unit& target) {
		int dmg = attack.calculateDamage(target.armor);
		target.health.decrease(dmg);
		target.notify({ UnitEventType::Damaged, target.id_, dmg, std::chrono::system_clock::now() });
		if (target.health.isZero()) {
			target.notify({ UnitEventType::Destroyed, target.id_, dmg, std::chrono::system_clock::now() });
		}
	}

	virtual void takeDamage(int dmg) {
		int finalDmg = dmg;
		armor.reduceDamage(finalDmg);
		health.decrease(finalDmg);
		notify({ UnitEventType::Damaged, id_, finalDmg, std::chrono::system_clock::now() });
		if (health.isZero()) {
			notify({ UnitEventType::Destroyed, id_, finalDmg, std::chrono::system_clock::now() });
		}
	}

	void subscribe(std::shared_ptr<IObserver> observer) override {
		observers_.push_back(observer);
	}

	void unsubscribe(std::shared_ptr<IObserver> observer) override {
		observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
	}

	void notify(const UnitEvent& event) override {
		for (auto& obs : observers_) {
			obs->onUnitEvent(event);
		}
	}

	int getId() const { return id_; }
	Point getPosition() const { return position; }
	char getSymbol() const { return symbol; }
	bool isAlive() const { return !health.isZero(); }
	std::shared_ptr<UnitTypeInfo> getInfo() const { return info_; }
};