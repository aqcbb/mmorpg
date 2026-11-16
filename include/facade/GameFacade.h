#pragma once
#include <memory>
#include <string>
#include "core/UnitType.h"

class GameMediator;
class Command;

class GameFacade {
private:
	std::shared_ptr<GameMediator> mediator_;

public:
	explicit GameFacade(std::shared_ptr<GameMediator> mediator);

    void createUnit(UnitType type, int x, int y);
    void moveUnit(int unitId, int x, int y);
    void attack(int attackerId, int targetId);
    void collectResource(int unitId, int resourcePointId);
    void heal(int unitId, int targetId);
    void buildBuilding(const std::string& type, int x, int y);
    void research(const std::string& techId);
    void distributeResources(const std::string& from, const std::string& to, int amount);
    void produceUnit(int buildingId, UnitType type);
    void getStats() const;

	void executeCommand(std::shared_ptr<Command> cmd);
	void processInput(const std::string& input);
};