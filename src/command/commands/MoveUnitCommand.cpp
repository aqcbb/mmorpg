#include "command/commands/MoveUnitCommand.h"
#include "mediator/GameMediator.h"

void MoveUnitCommand::execute() {
    if (auto med = mediator_.lock()) med->moveUnit(unitId_, x_, y_);
}