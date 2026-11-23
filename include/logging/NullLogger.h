#pragma once
#include "logging/ILogger.h"

class NullLogger : public ILogger {
public:
	void log(const LogEvent& event) override {}
	void setFormatter(std::shared_ptr<ILogFormatter> formatter) override {}
};