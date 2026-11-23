#pragma once
#include "logging/ILogFormatter.h"

class JsonFormatter : public ILogFormatter {
public:
	std::string format(const LogEvent& event) const override;
};