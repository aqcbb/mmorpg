#include "logging/TextFormatter.h"
#include <sstream>

std::string TextFormatter::format(const LogEvent& event) const {
	std::ostringstream oss;
	oss << "[" << event.timestamp << "] [" << event.level << "] [" << event.source << "] " << event.message;
	return oss.str();
}