#include "handler/handlers/BuildHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool BuildHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 5) != "build") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string b, typeStr, a, coords;
    iss >> b >> typeStr >> a >> coords;

    int x = 0, y = 0;
    char comma;
    std::istringstream coordsStream(coords);
    coordsStream >> x >> comma >> y;

    if (auto facade = facade_.lock()) {
        facade->buildBuilding(typeStr, x, y);
    }
    return true;
}