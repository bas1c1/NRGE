#include "../include/logger.h"

utils::logger::logger() {}
utils::logger::~logger() {}

std::string utils::logger::get_current_date() {
	auto ticks = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	char buffer[90];
	struct tm* timeinfo = new struct tm;
	localtime_s(timeinfo, &ticks);
	strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
	return std::string(buffer);
}

void utils::logger::critical(std::string str) {
	std::cout << get_current_date() << " ERROR - " << str << std::endl;
	utils::panic();
}

void utils::logger::debug(std::string str) {
	std::cout << get_current_date() << " DEBUG - " << str << std::endl;
}