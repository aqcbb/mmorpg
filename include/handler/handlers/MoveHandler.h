#pragma once
#include "handler/Handler.h"

class GameFacade;

class MoveHandler : public Handler {
private:
    std::weak_ptr<GameFacade> facade_;
public:
    explicit MoveHandler(std::weak_ptr<GameFacade> facade) : facade_(facade) {}
    bool handle(const std::string& cmd) override;
};