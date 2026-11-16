#pragma once
#include "command/Command.h"

class AttackCommand : public Command {
private:
    int attackerId_, targetId_;
public:
    AttackCommand(std::weak_ptr<GameMediator> m, int attackerId, int targetId)
        : Command(m), attackerId_(attackerId), targetId_(targetId) {
    }
    void execute() override;
};