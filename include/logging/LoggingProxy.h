#pragma once
#include "logging/ILogger.h"
#include <memory>

class LoggingProxy : public ILogger {
private:
	std::shared_ptr<ILogger> currentLogger_;
	std::shared_ptr<ILogFormatter> formatter_;

public:
	LoggingProxy();

	void log(const LogEvent& event) override;
	void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;

	void setLogger(std::unique_ptr<ILogger> logger);
	void setLoggerFromString(const std::string& type, const std::string& filename = "");
	void setFormatterFromString(const std::string& type);
};