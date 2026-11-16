#include "command/commands/AttackCommand.h"
#include "mediator/GameMediator.h"

void AttackCommand::execute() {
    if (auto med = mediator_.lock()) med->attack(attackerId_, targetId_);
}