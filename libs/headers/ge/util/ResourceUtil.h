#pragma once

#include <string>
#include <iostream>
#include <fstream>

namespace ge
{

	namespace ResourceUtil
	{
		int getRawStrResource(std::string path, std::string *fileOut);
		int getRawStrFile(std::string path, std::string *fileOut);
		std::string getResPath(std::string);
	}
}
