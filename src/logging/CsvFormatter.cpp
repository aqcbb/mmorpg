#include "logging/CsvFormatter.h"
#include <sstream>
#include <algorithm>

std::string cleanCsv(const std::string& s) {
    std::string out = s;
    std::replace(out.begin(), out.end(), ';', ' ');
    std::replace(out.begin(), out.end(), '\n', ' ');
    return out;
}

std::string CsvFormatter::format(const LogEvent& event) const {
    std::ostringstream oss;
    oss << event.timestamp << ";" << event.level << ";"
        << cleanCsv(event.source) << ";" << cleanCsv(event.message);
    return oss.str();
}