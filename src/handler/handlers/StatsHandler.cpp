#include "handler/handlers/StatsHandler.h"
#include "facade/GameFacade.h"
#include <iostream>

bool StatsHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 5) != "stats") return next_ ? next_->handle(cmd) : false;

    if (auto facade = facade_.lock()) {
        facade->getStats();
    }
    return true;
}