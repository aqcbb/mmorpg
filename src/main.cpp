#include <iostream>
#include "controller/GameController.h"

int main() {
	GameController controller(15, 15);
	controller.setup();

	controller.runCreationAndMovementScenario();
	controller.runTerrainProxyScenario();
	controller.runNeutralObjectsScenario();
	controller.runObserverDeathScenario();

	return 0;
}