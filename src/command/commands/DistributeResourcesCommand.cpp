#include "command/commands/DistributeResourcesCommand.h"
#include "mediator/GameMediator.h"

void DistributeResourcesCommand::execute() {
    if (auto med = mediator_.lock()) med->distributeResources(from_, to_, amount_);
}