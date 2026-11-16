#pragma once
#include "command/Command.h"
#include <string>

class BuildBuildingCommand : public Command {
private:
    std::string buildingType_;
    int x_, y_;
public:
    BuildBuildingCommand(std::weak_ptr<GameMediator> m, std::string type, int x, int y)
        : Command(m), buildingType_(type), x_(x), y_(y) {
    }
    void execute() override;
};