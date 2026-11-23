#include "handler/handlers/LoggerHandler.h"
#include "facade/GameFacade.h"
#include "logging/LoggingProxy.h"
#include <sstream>
#include <iostream>

bool LoggerHandler::handle(const std::string& cmd) {
	if (cmd.substr(0, 10) == "set_logger") {
		std::istringstream iss(cmd);
		std::string s, l, type, filename;
		iss >> s >> l >> type >> filename;

		if (auto facade = facade_.lock()) {
			auto logger = facade->getLogger();
			if (type == "file") {
				logger->setLoggerFromString("file", filename);
			}
			else {
				logger->setLoggerFromString(type);
			}
			std::cout << "[Logger] Switched to " << type << "\n";
		}
		return true;
	}

	if (cmd.substr(0, 10) == "set_format") {
		std::istringstream iss(cmd);
		std::string s, f, type;
		iss >> s >> f >> type;

		if (auto facade = facade_.lock()) {
			auto logger = facade->getLogger();
			logger->setFormatterFromString(type);
			std::cout << "[Logger] Switched format to " << type << "\n";
		}
		return true;
	}

	return next_ ? next_->handle(cmd) : false;
}

