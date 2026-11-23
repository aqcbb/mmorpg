#include "handler/handlers/SpawnObjectHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool SpawnObjectHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 12) != "spawn object") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string s, o, typeStr, at, coords;
    iss >> s >> o >> typeStr >> at >> coords;

    int x, y;
    char comma;
    std::istringstream cs(coords);
    cs >> x >> comma >> y;

    if (auto facade = facade_.lock()) {
        facade->spawnObject(typeStr, x, y);
    }
    return true;
}