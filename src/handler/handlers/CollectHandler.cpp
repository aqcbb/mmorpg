#include "handler/handlers/CollectHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool CollectHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 7) != "collect") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string c, u, id1, f, id2;
    iss >> c >> u >> id1 >> f >> id2;

    int unitId = std::stoi(id1);
    int resourceId = std::stoi(id2);

    if (auto facade = facade_.lock()) {
        facade->collectResource(unitId, resourceId);
    }
    return true;
}