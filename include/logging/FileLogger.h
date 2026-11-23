#pragma once
#include "logging/ILogger.h"
#include <fstream>

class FileLogger : public ILogger {
private:
	std::ofstream file_;
	std::shared_ptr<ILogFormatter> formatter_;
public:
	explicit FileLogger(const std::string& filename);
	~FileLogger() override;

	FileLogger(const FileLogger&) = delete;
	FileLogger& operator=(const FileLogger&) = delete;

	void log(const LogEvent& event) override;
	void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;
};