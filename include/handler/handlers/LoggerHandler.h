#pragma once
#include "handler/Handler.h"
#include <memory>

class GameFacade;

class LoggerHandler : public Handler {
private:
	std::weak_ptr<GameFacade> facade_;
public:
	explicit LoggerHandler(std::weak_ptr<GameFacade> facade) : facade_(facade) {}
	bool handle(const std::string& cmd) override;
};