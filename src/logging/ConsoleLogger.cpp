#include "logging/ConsoleLogger.h"
#include <iostream>

void ConsoleLogger::log(const LogEvent& event) {
	if (formatter_) {
		std::cout << formatter_->format(event) << "\n";
	}
}

void ConsoleLogger::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
	formatter_ = formatter;
}