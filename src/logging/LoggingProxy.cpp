#include "logging/LoggingProxy.h"
#include "logging/ConsoleLogger.h"
#include "logging/FileLogger.h"
#include "logging/NullLogger.h"
#include "logging/TextFormatter.h"
#include "logging/JsonFormatter.h"
#include "logging/CsvFormatter.h"
#include "logging/FormatterFactory.h"
#include <iostream>

LoggingProxy::LoggingProxy() {
	currentLogger_ = std::make_unique<ConsoleLogger>();
	formatter_ = std::make_shared<TextFormatter>();
	currentLogger_->setFormatter(formatter_);
}

void LoggingProxy::log(const LogEvent& event) {
	if (currentLogger_) currentLogger_->log(event);
}

void LoggingProxy::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
	formatter_ = formatter;
	if (currentLogger_) currentLogger_->setFormatter(formatter_);
}

void LoggingProxy::setLogger(std::unique_ptr<ILogger> logger) {
	currentLogger_ = std::move(logger);
	if (currentLogger_) currentLogger_->setFormatter(formatter_);
}

void LoggingProxy::setLoggerFromString(const std::string& type, const std::string& filename) {
	if (type == "console") setLogger(std::make_unique<ConsoleLogger>());
	else if (type == "file") setLogger(std::make_unique<FileLogger>(filename));
	else if (type == "null") setLogger(std::make_unique<NullLogger>());
}

void LoggingProxy::setFormatterFromString(const std::string& type) {
	try {
		auto newFormatter = FormatterFactory::createFormatter(type);
		setFormatter(newFormatter);
	}
	catch (const std::exception& e) {
		std::cout << "[Logger] Error: " << e.what() << "\n";
	}
}