#include "command/commands/ResearchCommand.h"
#include "mediator/GameMediator.h"

void ResearchCommand::execute() {
    if (auto med = mediator_.lock()) med->research(techId_);
}