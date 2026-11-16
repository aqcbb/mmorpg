#pragma once
#include "command/Command.h"
#include <string>

class ResearchCommand : public Command {
private:
    std::string techId_;
public:
    ResearchCommand(std::weak_ptr<GameMediator> m, std::string techId)
        : Command(m), techId_(techId) {
    }
    void execute() override;
};