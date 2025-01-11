#pragma once
#include "../utils.h"

#include <chrono>
#include <time.h>
#include <iostream>
#include <string>

namespace utils {
	class logger {
	public:
		logger();
		~logger();
		static void critical(std::string str);
		static void debug(std::string str);
	private:
		static std::string get_current_date();
	};
}