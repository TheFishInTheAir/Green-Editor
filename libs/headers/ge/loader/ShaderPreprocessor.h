#pragma once
#include <string>

#define ge_MAX_PREPROCESSOR_INCLUDES 30

namespace ge
{
	namespace ShaderPreprocessor
	{
		std::string process(std::string);
	}
}
