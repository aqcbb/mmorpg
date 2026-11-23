#include "logging/FileLogger.h"

FileLogger::FileLogger(const std::string& filename) {
	file_.open(filename, std::ios::app);
	if (!file_.is_open()) throw std::runtime_error("Failed to open log file: " + filename);
}

FileLogger::~FileLogger() {
	if (file_.is_open()) file_.close();
}

void FileLogger::log(const LogEvent& event) {
	if (formatter_ && file_.is_open()) {
		file_ << formatter_->format(event) << "\n";
	}
}

void FileLogger::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
	formatter_ = formatter;
}