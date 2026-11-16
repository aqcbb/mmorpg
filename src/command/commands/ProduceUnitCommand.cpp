#include "command/commands/ProduceUnitCommand.h"
#include "mediator/GameMediator.h"

void ProduceUnitCommand::execute() {
    if (auto med = mediator_.lock()) med->produceUnit(buildingId_, unitType_);
}