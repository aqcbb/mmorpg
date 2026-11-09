#include <iostream>
#include "controller/GameController.h"

int main() {
	GameController controller(40, 20);
	controller.setup();

	controller.runCreationAndMovementScenario();
	controller.runTerrainProxyScenario();
	controller.runNeutralObjectsScenario();
	controller.runObserverDeathScenario();

	return 0;
}