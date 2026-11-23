#include "handler/handlers/LoggerHandler.h"
#include "facade/GameFacade.h"
#include "logging/LoggingProxy.h"
#include <sstream>
#include <iostream>

bool LoggerHandler::handle(const std::string& cmd) {
    std::istringstream iss(cmd);
    std::string command;
    iss >> command;

    if (command == "set_logger") {
        std::string type, filename;
        iss >> type >> filename;

        if (auto facade = facade_.lock()) {
            auto logger = facade->getLogger();
            if (type == "file") {
                logger->setLoggerFromString("file", filename);
            }
            else {
                logger->setLoggerFromString(type);
            }
            logger->log(LogEvent("INFO", "SYSTEM", "Logger switched to " + type));
        }
        return true;
    }

    if (command == "set_format") {
        std::string type;
        iss >> type;

        if (auto facade = facade_.lock()) {
            auto logger = facade->getLogger();
            logger->setFormatterFromString(type);
            logger->log(LogEvent("INFO", "SYSTEM", "Format switched to " + type));
        }
        return true;
    }

    return next_ ? next_->handle(cmd) : false;
}

