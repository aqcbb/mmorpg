#include "command/commands/StatsCommand.h"
#include "mediator/GameMediator.h"

void StatsCommand::execute() {
    if (auto med = mediator_.lock()) med->getStats();
}