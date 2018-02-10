#pragma once
#include <string>

#define ge_MAX_PREPROCESSOR_INCLUDES 30

namespace ge
{
	namespace ShaderPreprocessor
	{
		//TODO: better name for both class and function
		std::string process(std::string);
	}
}
