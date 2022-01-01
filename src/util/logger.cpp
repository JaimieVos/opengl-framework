#include "log.h"

#include <ctime>
#include <sstream>
#include <iomanip>

namespace logger
{
	std::string logger::timestamp()
	{
		std::stringstream resultStream;
		std::time_t rawTime = std::time(nullptr);
		std::tm* localTime = std::localtime(&rawTime);

		resultStream << std::put_time(localTime, "%T");

		return resultStream.str();
	}
}