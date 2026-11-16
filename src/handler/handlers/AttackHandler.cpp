#include "handler/handlers/AttackHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool AttackHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 6) != "attack") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string a, u, id1, t, id2;
    iss >> a >> u >> id1 >> t >> id2;

    int attackerId = std::stoi(id1);
    int targetId = std::stoi(id2);

    if (auto facade = facade_.lock()) {
        facade->attack(attackerId, targetId);
    }
    return true;
}