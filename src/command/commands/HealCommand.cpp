#include "command/commands/HealCommand.h"
#include "mediator/GameMediator.h"

void HealCommand::execute() {
    if (auto med = mediator_.lock()) med->heal(unitId_, targetId_);
}