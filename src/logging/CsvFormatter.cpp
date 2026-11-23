#include "logging/CsvFormatter.h"
#include <sstream>

std::string CsvFormatter::format(const LogEvent& event) const {
	std::ostringstream oss;
	oss << event.timestamp << ";" << event.level << ";" << event.source << ";" << event.message;
	return oss.str();
}