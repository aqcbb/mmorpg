#pragma once
#include "logging/ILogger.h"

class ConsoleLogger : public ILogger {
private:
	std::shared_ptr<ILogFormatter> formatter_;
public:
	void log(const LogEvent& event) override;
	void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;
};