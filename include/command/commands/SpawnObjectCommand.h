#pragma once
#include "command/Command.h"
#include <string>

class SpawnObjectCommand : public Command {
private:
    std::string type_;
    int x_, y_;
public:
    SpawnObjectCommand(std::weak_ptr<GameMediator> m, std::string type, int x, int y)
        : Command(m), type_(type), x_(x), y_(y) {
    }
    void execute() override;
};