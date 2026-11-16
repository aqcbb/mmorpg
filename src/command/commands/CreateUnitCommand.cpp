#include "command/commands/CreateUnitCommand.h"
#include "mediator/GameMediator.h"

void CreateUnitCommand::execute() {
    if (auto med = mediator_.lock()) med->createUnit(type_, x_, y_);
}