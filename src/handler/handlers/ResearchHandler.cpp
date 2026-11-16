#include "handler/handlers/ResearchHandler.h"
#include "facade/GameFacade.h"
#include <sstream>
#include <iostream>

bool ResearchHandler::handle(const std::string& cmd) {
    if (cmd.substr(0, 8) != "research") return next_ ? next_->handle(cmd) : false;

    std::istringstream iss(cmd);
    std::string r, techId;
    iss >> r >> techId;

    if (auto facade = facade_.lock()) {
        facade->research(techId);
    }
    return true;
}