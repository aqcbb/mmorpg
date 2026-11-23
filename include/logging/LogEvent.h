#pragma once
#include <string>

class LogEvent {
public:
	std::string timestamp;
	std::string level;
	std::string source;
	std::string message;

	LogEvent(std::string lvl, std::string src, std::string msg);

	static std::string getCurrentTimestamp();
};