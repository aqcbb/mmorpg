#pragma once

#include "IObserver.h"
#include <memory>

class IObservable {
public:
	virtual ~IObservable() = default;
	virtual void subscribe(std::shared_ptr<IObserver> observer) = 0;
	virtual void unsubscribe(std::shared_ptr<IObserver> observer) = 0;
	virtual void notify(const UnitEvent& event) = 0;
};