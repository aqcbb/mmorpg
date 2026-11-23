#include "logging/JsonFormatter.h"
#include <sstream>

std::string escapeJson(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (c == '"') out += "\\\"";
        else if (c == '\\') out += "\\\\";
        else out += c;
    }
    return out;
}

std::string JsonFormatter::format(const LogEvent& event) const {
    std::ostringstream oss;
    oss << "{\"timestamp\":\"" << event.timestamp
        << "\", \"level\":\"" << event.level
        << "\", \"source\":\"" << escapeJson(event.source)
        << "\", \"message\":\"" << escapeJson(event.message) << "\"}";
    return oss.str();
}