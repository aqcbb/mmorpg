#pragma once
#include <memory>
#include <string>
#include "core/UnitType.h"
#include "terrain/TerrainMap.h"
#include "logging/ILogger.h"
#include "field/GameField.h"
#include "neutral/NeutralObject.h"

class Base;
class UnitManager;
class BuildingManager;
class ResourceSystem;
class CombatSystem;

class GameMediator {
private:
    std::shared_ptr<ILogger> logger_;

    std::shared_ptr<Base> base_;
    std::shared_ptr<UnitManager> unitManager_;
    std::shared_ptr<BuildingManager> buildingManager_;
    std::shared_ptr<ResourceSystem> resourceSystem_;
    std::shared_ptr<CombatSystem> combatSystem_;

    std::vector<std::vector<std::shared_ptr<NeutralObject>>> objects_;

    std::shared_ptr<GameField> gameField_;
    std::shared_ptr<TerrainMap> terrainMap_;

public:
    GameMediator(std::shared_ptr<ILogger> logger);

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
    void spawnObject(const std::string& type, int x, int y);

    void notifyUnitCreated(int unitId);
    void notifyResourceCollected(int unitId, int amount);
    void notifyCombatResolved(int attackerId, int targetId, int damage);
    void notifyBuildingCompleted(int buildingId);
    void notifyResearchCompleted(const std::string& tech);

    std::shared_ptr<UnitManager> getUnitManager() const { return unitManager_; }
    std::shared_ptr<BuildingManager> getBuildingManager() const { return buildingManager_; }

    std::shared_ptr<NeutralObject> getObjectAt(int x, int y) const;

    std::shared_ptr<GameField> getGameField() const { return gameField_; }
    std::shared_ptr<TerrainMap> getTerrainMap() const { return terrainMap_; }
};