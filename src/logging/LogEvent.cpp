#include "logging/LogEvent.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

LogEvent::LogEvent(std::string lvl, std::string src, std::string msg)
	: level(std::move(lvl)), source(std::move(src)), message(std::move(msg)) {
	timestamp = getCurrentTimestamp();
}

std::string	LogEvent::getCurrentTimestamp() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm bt{};
#ifdef _WIN32
	localtime_s(&bt, &in_time_t);
#else
	localtime_r(&in_time_t, &bt);
#endif
	std::ostringstream oss;
	oss << std::put_time(&bt, "%Y-%m-%dT%H:%M:%S");
	return oss.str();
}