#pragma once
#include "handler/Handler.h"

class GameFacade;

class ResearchHandler : public Handler {
private:
    std::weak_ptr<GameFacade> facade_;
public:
    explicit ResearchHandler(std::weak_ptr<GameFacade> facade) : facade_(facade) {}
    bool handle(const std::string& cmd) override;
};