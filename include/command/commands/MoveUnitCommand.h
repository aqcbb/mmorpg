#pragma once
#include "command/Command.h"

class MoveUnitCommand : public Command {
private:
    int unitId_, x_, y_;
public:
    MoveUnitCommand(std::weak_ptr<GameMediator> m, int unitId, int x, int y)
        : Command(m), unitId_(unitId), x_(x), y_(y) {
    }
    void execute() override;
};