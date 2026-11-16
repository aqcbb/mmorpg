#include "core/Colors.h"

#include "facade/GameFacade.h"
#include "mediator/GameMediator.h"
#include "command/Command.h"

#include "terrain/TerrainMap.h"
#include "units/Unit.h"
#include "building/Building.h"
#include "manager/UnitManager.h"
#include "manager/BuildingManager.h"

#include "command/commands/CreateUnitCommand.h"
#include "command/commands/MoveUnitCommand.h"
#include "command/commands/AttackCommand.h"
#include "command/commands/CollectResourceCommand.h"
#include "command/commands/HealCommand.h"
#include "command/commands/BuildBuildingCommand.h"
#include "command/commands/ResearchCommand.h"
#include "command/commands/DistributeResourcesCommand.h"
#include "command/commands/ProduceUnitCommand.h"
#include "command/commands/StatsCommand.h"

#include "handler/handlers/CreateHandler.h"
#include "handler/handlers/MoveHandler.h"
#include "handler/handlers/AttackHandler.h"
#include "handler/handlers/CollectHandler.h"
#include "handler/handlers/HealHandler.h"
#include "handler/handlers/BuildHandler.h"
#include "handler/handlers/ResearchHandler.h"
#include "handler/handlers/ProduceHandler.h"
#include "handler/handlers/StatsHandler.h"
#include "handler/handlers/MapHandler.h"
#include "handler/handlers/DistributeHandler.h"

#include <iostream>

GameFacade::GameFacade(std::shared_ptr<GameMediator> mediator)
    : mediator_(mediator)
{
}

void GameFacade::init() {
    auto create = std::make_shared<CreateHandler>(shared_from_this());
    auto move = std::make_shared<MoveHandler>(shared_from_this());
    auto attack = std::make_shared<AttackHandler>(shared_from_this());
    auto collect = std::make_shared<CollectHandler>(shared_from_this());
    auto distribute = std::make_shared<DistributeHandler>(shared_from_this());
    auto heal = std::make_shared<HealHandler>(shared_from_this());
    auto build = std::make_shared<BuildHandler>(shared_from_this());
    auto research = std::make_shared<ResearchHandler>(shared_from_this());
    auto produce = std::make_shared<ProduceHandler>(shared_from_this());
    auto stats = std::make_shared<StatsHandler>(shared_from_this());
    auto mapHandler = std::make_shared<MapHandler>(shared_from_this());

    create->setNext(move);
    move->setNext(attack);
    attack->setNext(collect);
    collect->setNext(distribute);
    distribute->setNext(heal);
    heal->setNext(build);
    build->setNext(research);
    research->setNext(produce);
    produce->setNext(stats);
    stats->setNext(mapHandler);
    mapHandler->setNext(nullptr);

    handlerChain_ = create;
}

void GameFacade::executeCommand(std::shared_ptr<Command> cmd) {
    if (cmd) {
        cmd->execute();
        history_.push(cmd);
    }
}

void GameFacade::processInput(const std::string& input) {
    if (!handlerChain_ || !handlerChain_->handle(input)) {
        std::cout << "[Facade] Unknown or invalid command: " << input << "\n";
    }

    if (input != "exit" && input != "quit" && input != "stats" && input != "map") {
        renderMap();
    }
}

void GameFacade::createUnit(UnitType type, int x, int y) {
    executeCommand(std::make_shared<CreateUnitCommand>(mediator_, type, x, y));
}

void GameFacade::moveUnit(int unitId, int x, int y) {
    executeCommand(std::make_shared<MoveUnitCommand>(mediator_, unitId, x, y));
}

void GameFacade::attack(int attackerId, int targetId) {
    executeCommand(std::make_shared<AttackCommand>(mediator_, attackerId, targetId));
}

void GameFacade::collectResource(int unitId, int resourcePointId) {
    executeCommand(std::make_shared<CollectResourceCommand>(mediator_, unitId, resourcePointId));
}

void GameFacade::heal(int unitId, int targetId) {
    executeCommand(std::make_shared<HealCommand>(mediator_, unitId, targetId));
}

void GameFacade::buildBuilding(const std::string& type, int x, int y) {
    executeCommand(std::make_shared<BuildBuildingCommand>(mediator_, type, x, y));
}

void GameFacade::research(const std::string& techId) {
    executeCommand(std::make_shared<ResearchCommand>(mediator_, techId));
}

void GameFacade::distributeResources(const std::string& from, const std::string& to, int amount) {
    executeCommand(std::make_shared<DistributeResourcesCommand>(mediator_, from, to, amount));
}

void GameFacade::produceUnit(int buildingId, UnitType type) {
    executeCommand(std::make_shared<ProduceUnitCommand>(mediator_, buildingId, type));
}

void GameFacade::getStats() const {
    if (mediator_) {
        mediator_->getStats();
    }
}

void GameFacade::renderMap() const {
    if (!mediator_) return;

    auto unitMgr = mediator_->getUnitManager();
    auto bldMgr = mediator_->getBuildingManager();
    auto terrainMgr = mediator_->getTerrainMap();

    int width = terrainMgr->getWidth();
    int height = terrainMgr->getHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
                std::cout << Color::GRAY << 'X' << Color::RESET;
                continue;
            }

            if (x == 1 && y == 1) {
                std::cout << Color::WHITE << 'B' << Color::RESET;
                continue;
            }

            bool drawn = false;

            for (const auto& b : bldMgr->getAllBuildings()) {
                if (b->getX() == x && b->getY() == y) {
                    std::cout << Color::MAGENTA << b->getSymbol() << Color::RESET;
                    drawn = true;
                    break;
                }
            }
            if (drawn) continue;

            for (const auto& u : unitMgr->getAllUnits()) {
                if (u->getPosition().x == x && u->getPosition().y == y) {
                    std::string type = u->getType();
                    if (type == "Infantry") std::cout << Color::RED << u->getSymbol() << Color::RESET;
                    else if (type == "Scout") std::cout << Color::CYAN << u->getSymbol() << Color::RESET;
                    else if (type == "Tank") std::cout << Color::BLUE << u->getSymbol() << Color::RESET;
                    else if (type == "Worker") std::cout << Color::YELLOW << u->getSymbol() << Color::RESET;
                    else if (type == "Medic") std::cout << Color::LRED << u->getSymbol() << Color::RESET;
                    else std::cout << u->getSymbol();
                    drawn = true;
                    break;
                }
            }
            if (drawn) continue;

            auto terr = terrainMgr->getTerrainAt(x, y);
            char sym = terr->getSymbol();
            if (sym == '.') std::cout << Color::GREEN << '.' << Color::RESET;
            else if (sym == '^') std::cout << Color::LGREEN << '^' << Color::RESET;
            else if (sym == '~') std::cout << Color::BLUE << '~' << Color::RESET;
            else if (sym == 'M') std::cout << Color::WHITE << 'M' << Color::RESET;
            else std::cout << sym;
        }
        std::cout << '\n';
    }
}