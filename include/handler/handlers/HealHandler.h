#pragma once
#include "handler/Handler.h"

class GameFacade;

class HealHandler : public Handler {
private:
    std::weak_ptr<GameFacade> facade_;
public:
    explicit HealHandler(std::weak_ptr<GameFacade> facade) : facade_(facade) {}
    bool handle(const std::string& cmd) override;
};