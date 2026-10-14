#include <iostream>
#include <vector>
#include "field/GameField.h"
#include "field/GameFieldIterator.h"
#include "factories/SwordsmanFactory.h"
#include "factories/SpearmanFactory.h"
#include "factories/LightArcherFactory.h"
#include "factories/HeavyArcherFactory.h"
#include "factories/CataphractFactory.h"
#include "factories/HorseArcherFactory.h"

void runCreateFieldScenario() {
    std::cout << "\nCreate field and fill via factories\n";

    GameField field(40, 20, 10);

    SwordsmanFactory    swordsmanFactory;
    SpearmanFactory     spearmanFactory;
    LightArcherFactory  lightArcherFactory;
    HeavyArcherFactory  heavyArcherFactory;
    CataphractFactory   cataphractFactory;
    HorseArcherFactory  horseArcherFactory;

    field.addUnit(swordsmanFactory.createUnit(),    1, 1);
    field.addUnit(spearmanFactory.createUnit(),     5, 3);
    field.addUnit(lightArcherFactory.createUnit(),  10, 5);
    field.addUnit(heavyArcherFactory.createUnit(),  15, 8);
    field.addUnit(cataphractFactory.createUnit(),   20, 10);
    field.addUnit(horseArcherFactory.createUnit(),  25, 12);

    std::cout << "Field size: " << field.size() << " units\n";
    field.draw(std::cout);
}

void runDeepCopyScenario() {
    std::cout << "\nDeep copy\n";

    GameField original(20, 10, 5);
    SwordsmanFactory swordsman;
    LightArcherFactory archer;

    original.addUnit(swordsman.createUnit(),    1, 1);
    original.addUnit(archer.createUnit(),       5, 5);

    std::cout << "Original size: " << original.size() << "\n";

    GameField copy = original;
    std::cout << "Copy size after copy ctor: " << copy.size() << "\n";

    Unit* u1 = original.getUnit(5, 5);
    Unit* u2 = copy.getUnit(5, 5);
    std::cout << "Original unit ptr: " << u1 << "\n";
    std::cout << "Copy unit ptr:     " << u2 << "\n";
    std::cout << "Pointers differ?   " << (u1 != u2 ? "YES (deep copy)" : "NO (shallow)") << "\n";
}

void runMoveScenario() {
    std::cout << "\nMove semantics\n";

    GameField source(20, 10, 5);
    SwordsmanFactory swordsman;
    source.addUnit(swordsman.createUnit(), 1, 1);
    source.addUnit(swordsman.createUnit(), 3, 3);

    std::cout << "Source size before move: " << source.size() << "\n";

    GameField moved = std::move(source);

    std::cout << "Moved size: " << moved.size() << "\n";
    std::cout << "Source size after move: " << source.size() << "\n";
    std::cout << "(source is now empty because its data was moved)\n";

    GameField target(10, 5, 3);
    target.addUnit(swordsman.createUnit(), 1, 1);
    std::cout << "Target size before move-assign: " << target.size() << "\n";
    target = std::move(moved);
    std::cout << "Target size after move-assign:  " << target.size() << "\n";
    std::cout << "Moved size after move-assign:   " << moved.size() << "\n";
}

void runMassDamageScenario() {
    std::cout << "\nIterate and apply mass action\n";

    GameField field(30, 15, 10);
    SwordsmanFactory swordsman;
    LightArcherFactory archer;
    CataphractFactory cataphract;

    field.addUnit(swordsman.createUnit(),   1, 1);
    field.addUnit(swordsman.createUnit(),   5, 2);
    field.addUnit(archer.createUnit(),      10, 5);
    field.addUnit(archer.createUnit(),      12, 7);
    field.addUnit(cataphract.createUnit(),  20, 10);

    std::cout << "Before mass damage\n";
    for (auto it = field.begin(); it != field.end(); ++it) {
        Unit* u = *it;
        std::cout << u->getType() << " at (" << u->getPosition().x << ", " << u->getPosition().y << ")\n";
    }

    for (auto it = field.begin(); it != field.end(); ++it) {
        (*it)->takeDamage(100);
    }

    std::cout << "After 100 damage to all\n";
    for (auto it = field.begin(); it != field.end(); ++it) {
        Unit* u = *it;
        std::cout << u->getType() << " alive? " << (u->isAlive() ? "yes" : "no") << "\n";
    }
}

void runRemoveDuringIterationScenario() {
    std::cout << "\nSafe removal during iteration\n";

    GameField field(20, 10, 10);
    SwordsmanFactory swordsman;
    for (int i = 0; i < 6; ++i) {
        field.addUnit(swordsman.createUnit(), 1 + i * 3, 1 + i);
    }

    std::cout << "Before: " << field.size() << " units\n";

    std::vector<std::pair<int, int>> toRemove;
    for (auto it = field.begin(); it != field.end(); ++it) {
        Unit* u = *it;
        if (u->getPosition().y % 2 == 0) {
            toRemove.push_back({ u->getPosition().x, u->getPosition().y });
        }
    }

    for (auto& pos : toRemove) {
        field.removeUnit(pos.first, pos.second);
    }
    
    std::cout << "After removal: " << field.size() << " units\n";
    field.draw(std::cout);
}

void runRuleOfFiveScenario() {
    std::cout << "\nRule of five\n";

    SwordsmanFactory swordsman;

    GameField a(10, 5, 3);
    a.addUnit(swordsman.createUnit(), 1, 1);
    std::cout << "[1] Default ctor  : size = " << a.size() << "\n";

    GameField b = a;
    std::cout << "[2] Copy ctor     : size = " << b.size() << "\n";

    GameField c(5, 5, 2);
    c = a;
    std::cout << "[3] Copy asssign  : size = " << c.size() << "\n";

    GameField d = std::move(b);
    std::cout << "[4] Move ctor     : d.size = " << d.size()
        << ", b.size = " << b.size() << "\n";

    GameField e(5, 5, 2);
    e = std::move(c);
    std::cout << "[5] Move assign   : e.size = " << e.size()
        << ", c.size = " << c.size() << "\n";
}

int main() {
    runCreateFieldScenario();
    runDeepCopyScenario();
    runMoveScenario();
    runMassDamageScenario();
    runRemoveDuringIterationScenario();
    runRuleOfFiveScenario();

    return 0;
}