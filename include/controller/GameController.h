#pragma once
#include "base/Base.h"
#include "terrain/TerrainMap.h"
#include "field/GameField.h"
#include "neutral/objects/TreasureChest.h"
#include "neutral/objects/Trap.h"
#include "neutral/objects/Altar.h"
#include "neutral/objects/EnergySource.h"
#include <memory>
#include <vector>

class GameController {
private:
	std::shared_ptr<Base> base_;
	std::shared_ptr<TerrainMap> terrain_;
	GameField field_;

	std::vector<std::vector<std::shared_ptr<NeutralObject>>> objects_;

	Point basePosition_{ 1, 1 };

	std::shared_ptr<Unit> findUnit(int id) const;
public:
	GameController(int width, int height);

	void setup();

	void spawnUnit(UnitType type, int x, int y);
	void moveUnit(int unitId, int newX, int newY);
	void interactWithObject(int unitId, int objX, int objY);

	void runCreationAndMovementScenario();
	void runTerrainProxyScenario();
	void runNeutralObjectsScenario();
	void runObserverDeathScenario();

	void drawField() const;
};