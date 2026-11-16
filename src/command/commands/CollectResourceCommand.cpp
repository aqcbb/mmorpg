#include "command/commands/CollectResourceCommand.h"
#include "mediator/GameMediator.h"

void CollectResourceCommand::execute() {
    if (auto med = mediator_.lock()) med->collectResource(unitId_, resourcePointId_);
}