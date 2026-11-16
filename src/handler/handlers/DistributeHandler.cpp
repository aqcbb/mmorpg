#include "handler/handlers/DistributeHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool DistributeHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 10) != "distribute") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string d, from, t, to, amountStr;
    iss >> d >> from >> t >> to >> amountStr;

    int amount = std::stoi(amountStr);

    if (auto facade = facade_.lock()) {
        facade->distributeResources(from, to, amount);
    }
    return true;
}