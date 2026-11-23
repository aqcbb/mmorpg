#include "command/commands/SpawnObjectCommand.h"
#include "mediator/GameMediator.h"

void SpawnObjectCommand::execute() {
    if (auto med = mediator_.lock()) {
        med->spawnObject(type_, x_, y_);
    }
}