#include "logging/FormatterFactory.h"
#include "logging/TextFormatter.h"
#include "logging/JsonFormatter.h"
#include "logging/CsvFormatter.h"
#include <stdexcept>

std::shared_ptr<ILogFormatter> FormatterFactory::createFormatter(const std::string& type) {
    if (type == "text") {
        return std::make_shared<TextFormatter>();
    }
    else if (type == "json") {
        return std::make_shared<JsonFormatter>();
    }
    else if (type == "csv") {
        return std::make_shared<CsvFormatter>();
    }
    throw std::invalid_argument("Unknown formatter type: " + type);
}