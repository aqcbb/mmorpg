#pragma once
#include "command/Command.h"
#include "core/UnitType.h"

class CreateUnitCommand : public Command {
private:
    UnitType type_;
    int x_, y_;
public:
    CreateUnitCommand(std::weak_ptr<GameMediator> m, UnitType type, int x, int y)
        : Command(m), type_(type), x_(x), y_(y) {
    }
    void execute() override;
};