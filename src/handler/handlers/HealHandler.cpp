#include "handler/handlers/HealHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool HealHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 4) != "heal") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string h, u, id1, t, id2;
    iss >> h >> u >> id1 >> t >> id2;

    int unitId = std::stoi(id1);
    int targetId = std::stoi(id2);

    if (auto facade = facade_.lock()) {
        facade->heal(unitId, targetId);
    }
    return true;
}