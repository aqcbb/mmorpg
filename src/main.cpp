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

    facade->processInput("");

    std::string input;
    while (true) {
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