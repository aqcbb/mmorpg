#pragma once
#include "command/Command.h"

class CollectResourceCommand : public Command {
private:
    int unitId_, resourcePointId_;
public:
    CollectResourceCommand(std::weak_ptr<GameMediator> m, int unitId, int resId)
        : Command(m), unitId_(unitId), resourcePointId_(resId) {
    }
    void execute() override;
};