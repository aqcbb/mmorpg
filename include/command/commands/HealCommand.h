#pragma once
#include "command/Command.h"

class HealCommand : public Command {
private:
    int unitId_, targetId_;
public:
    HealCommand(std::weak_ptr<GameMediator> m, int unitId, int targetId)
        : Command(m), unitId_(unitId), targetId_(targetId) {
    }
    void execute() override;
};