#pragma once
#include "logging/LogEvent.h"

class ILogFormatter {
public:
	virtual ~ILogFormatter() = default;
	virtual std::string format(const LogEvent& event) const = 0;
};