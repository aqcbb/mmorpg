#include "handler/handlers/MapHandler.h"
#include "facade/GameFacade.h"
#include <iostream>

bool MapHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 3) != "map") {
        return next_ ? next_->handle(cmd) : false;
    }

    if (auto facade = facade_.lock()) {
        facade->renderMap();
    }
    return true;
}