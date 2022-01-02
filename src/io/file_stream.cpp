#include "file_stream.h"

#include "util/logger.h"

#include <fstream>
#include <sstream>

namespace file_stream
{
	std::string readFile(const char* path)
	{
		std::string stringContent;
		std::ifstream stream;

		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			std::stringstream content;

			stream.open(path);
			content << stream.rdbuf();
			stream.close();

			stringContent = content.str();
		}
		catch (const std::exception& exception)
		{
			logger::error(exception.what());
		}

		return stringContent;
	}
}