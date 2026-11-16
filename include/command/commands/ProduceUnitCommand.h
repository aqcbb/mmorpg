#pragma once
#include "command/Command.h"
#include "core/UnitType.h"

class ProduceUnitCommand : public Command {
private:
    int buildingId_;
    UnitType unitType_;
public:
    ProduceUnitCommand(std::weak_ptr<GameMediator> m, int buildingId, UnitType type)
        : Command(m), buildingId_(buildingId), unitType_(type) {
    }
    void execute() override;
};