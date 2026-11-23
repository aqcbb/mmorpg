#include "mediator/GameMediator.h"
#include "facade/GameFacade.h"
#include "logging/LoggingProxy.h"
#include <iostream>
#include <string>

int main() {
    auto logger = std::make_shared<LoggingProxy>();
    auto mediator = std::make_shared<GameMediator>(logger);
    auto facade = std::make_shared<GameFacade>(mediator, logger);
    facade->init();

    facade->renderMap();

    std::cout << "\nInteractive Mode\n";

    std::cout << "Available commands:\n";
    std::cout << "  create unit <type> at <x>,<y>   (types: infantry, scout, tank, worker, medic)\n";
    std::cout << "  move unit <id> to <x>,<y>\n";
    std::cout << "  attack unit <id> target <id>\n";
    std::cout << "  build <type> at <x>,<y>          (types: barracks, powerplant, laboratory, warehouse, hospital)\n";
    std::cout << "  stats\n";
    std::cout << "  exit\n\n";

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            break;
        }
        if (input.empty()) {
            continue;
        }

        facade->processInput(input);
    }

    std::cout << "Game closed.\n";
    return 0;
}