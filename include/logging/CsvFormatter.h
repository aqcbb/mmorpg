#pragma once
#include "logging/ILogFormatter.h"

class CsvFormatter : public ILogFormatter {
public:
	std::string format(const LogEvent& event) const override;
};