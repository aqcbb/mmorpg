#include "command/commands/BuildBuildingCommand.h"
#include "mediator/GameMediator.h"

void BuildBuildingCommand::execute() {
    if (auto med = mediator_.lock()) med->buildBuilding(buildingType_, x_, y_);
}