#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "command/Command.h"

class CommandHistory {
private:
    std::vector<std::shared_ptr<Command>> history_;
public:
    void push(std::shared_ptr<Command> cmd) {
        history_.push_back(cmd);
    }

    void undo() {
        if (!history_.empty()) {
            history_.pop_back();
            std::cout << "[History] Last command removed from history.\n";
        } else {
            std::cout << "[History] History is empty.\n";
        }
    }

    std::shared_ptr<Command> getLastCommand() const {
        if (history_.empty()) return nullptr;
        return history_.back();
    }
};