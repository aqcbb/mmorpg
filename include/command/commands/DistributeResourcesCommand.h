#pragma once
#include "command/Command.h"
#include <string>

class DistributeResourcesCommand : public Command {
private:
    std::string from_, to_;
    int amount_;
public:
    DistributeResourcesCommand(std::weak_ptr<GameMediator> m, std::string from, std::string to, int amount)
        : Command(m), from_(from), to_(to), amount_(amount) {
    }
    void execute() override;
};