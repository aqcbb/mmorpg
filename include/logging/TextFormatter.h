#pragma once
#include "logging/ILogFormatter.h"

class TextFormatter : public ILogFormatter {
public:
	std::string format(const LogEvent& event) const override;
};