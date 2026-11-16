#include "handler/handlers/MoveHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool MoveHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 4) != "move") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string m, u, idStr, t, coords;
    iss >> m >> u >> idStr >> t >> coords;

    int id = std::stoi(idStr);
    int x = 0, y = 0;
    char comma;
    std::istringstream coordsStream(coords);
    coordsStream >> x >> comma >> y;

    if (auto facade = facade_.lock()) {
        facade->moveUnit(id, x, y);
    }
    return true;
}