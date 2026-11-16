#include "mediator/GameMediator.h"
#include "facade/GameFacade.h"
#include <iostream>
#include <string>

int main() {
    auto mediator = std::make_shared<GameMediator>();
    auto facade = std::make_shared<GameFacade>(mediator);

    facade->init();

    std::cout << "\n(!) Scenario 1: Creation & Stats\n\n";
    facade->processInput("create unit infantry at 5,5");
    facade->processInput("create unit scout at 6,5");
    facade->processInput("stats");  

    std::cout << "\n(!) Scenario 2: Move & Attack\n\n";
    facade->processInput("move unit 1 to 10,10");
    facade->processInput("attack unit 1 target 2");
    facade->processInput("stats");

    std::cout << "\n(!) Scenario 3: Build & Research\n\n";
    facade->processInput("build barracks at 3,3");
    facade->processInput("research attack_upgrade");
    facade->processInput("produce infantry in 1");
    facade->processInput("stats");

    std::cout << "\n(!) Scenario 4: Collect & Distribute Resources\n\n";
    facade->processInput("create unit worker at 15,10");
    facade->processInput("collect unit 3 from 1");
    facade->processInput("distribute wood to barracks 50");
    facade->processInput("stats");

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