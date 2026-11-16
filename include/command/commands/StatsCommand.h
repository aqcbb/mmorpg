#pragma once
#include "command/Command.h"
#include <string>

class StatsCommand : public Command {
private:
    std::string statsType_;
public:
    StatsCommand(std::weak_ptr<GameMediator> m, std::string type)
        : Command(m), statsType_(type) {
    }
    void execute() override;
};