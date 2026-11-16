#include "handler/handlers/ProduceHandler.h"
#include "facade/GameFacade.h"
#include "core/UnitType.h"
#include <sstream>
#include <iostream>

bool ProduceHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 7) != "produce") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string p, typeStr, in, idStr;
    iss >> p >> typeStr >> in >> idStr;

    int buildingId = std::stoi(idStr);
    UnitType type;
    if (typeStr == "infantry") type = UnitType::Infantry;
    else if (typeStr == "scout") type = UnitType::Scout;
    else if (typeStr == "tank") type = UnitType::Tank;
    else if (typeStr == "worker") type = UnitType::Worker;
    else if (typeStr == "medic") type = UnitType::Medic;
    else {
        std::cout << "[ProduceHandler] Unknown unit type: " << typeStr << "\n";
        return true;
    }

    if (auto facade = facade_.lock()) {
        facade->produceUnit(buildingId, type);
    }
    return true;
}