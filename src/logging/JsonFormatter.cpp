#include "logging/JsonFormatter.h"
#include <sstream>

std::string JsonFormatter::format(const LogEvent& event) const {
	std::ostringstream oss;
	oss << "{\"timestamp\":\"" << event.timestamp
		<< "\", \"level\":\"" << event.level
		<< "\", \"source\":\"" << event.source
		<< "\", \"message\":\"" << event.message << "\"}";
	return oss.str();
}