#pragma once
#include "handler/Handler.h"
#include <memory>

class GameFacade;

class MapHandler : public Handler {
private:
    std::weak_ptr<GameFacade> facade_;
public:
    explicit MapHandler(std::weak_ptr<GameFacade> facade) : facade_(facade) {}
    bool handle(const std::string& cmd) override;
};