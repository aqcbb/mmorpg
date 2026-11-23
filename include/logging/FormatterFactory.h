#pragma once
#include "logging/ILogFormatter.h"
#include <string>
#include <memory>

class FormatterFactory {
public:
    static std::shared_ptr<ILogFormatter> createFormatter(const std::string& type);
};