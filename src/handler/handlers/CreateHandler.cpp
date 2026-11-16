#include "handler/handlers/CreateHandler.h"
#include "facade/GameFacade.h"
#include "core/UnitType.h"
#include <sstream>
#include <iostream>

bool CreateHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 6) != "create") {
        return next_ ? next_->handle(cmd) : false;
    }

    std::istringstream iss(cmd);
    std::string c, u, typeStr, at, coords;
    iss >> c >> u >> typeStr >> at >> coords;

    UnitType type;
    if (typeStr == "infantry") type = UnitType::Infantry;
    else if (typeStr == "scout") type = UnitType::Scout;
    else if (typeStr == "tank") type = UnitType::Tank;
    else if (typeStr == "worker") type = UnitType::Worker;
    else if (typeStr == "medic") type = UnitType::Medic;
    else {
        std::cout << "[CreateHandler] Unknown unit type: " << typeStr << "\n";
        return true;
    }

    int x = 0, y = 0;
    char comma;
    std::istringstream cs(coords);
    cs >> x >> comma >> y;

    if (auto facade = facade_.lock()) {
        facade->createUnit(type, x, y);
    }
    return true;
}