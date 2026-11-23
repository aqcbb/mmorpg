#pragma once
#include "handler/Handler.h"
#include <memory>

class GameFacade;

class SpawnObjectHandler : public Handler {
private:
    std::weak_ptr<GameFacade> facade_;
public:
    explicit SpawnObjectHandler(std::weak_ptr<GameFacade> facade) : facade_(facade) {}
    bool handle(const std::string& cmd) override;
};