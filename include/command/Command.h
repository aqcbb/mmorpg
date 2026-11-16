#pragma once
#include <memory>

class GameMediator;

class Command {
protected:
	std::weak_ptr<GameMediator> mediator_;

public:
	explicit Command(std::weak_ptr<GameMediator> mediator) : mediator_(std::move(mediator)) {}

	virtual ~Command() = default;
	virtual void execute() = 0;
};