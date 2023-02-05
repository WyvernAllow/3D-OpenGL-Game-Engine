#include "Utils.h"
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>

namespace engine::utils
{
	std::string ReadText(const std::string& path)
	{
		if (!std::filesystem::exists(path))
		{
			std::cerr << "File at " << path << " does not exist.\n";
		}

		std::ifstream file(path);
		std::stringstream buffer;
		buffer << file.rdbuf();

		return buffer.str();
	}
}

