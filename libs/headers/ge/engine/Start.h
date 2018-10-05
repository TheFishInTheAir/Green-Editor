#pragma once
#include <ge/graphics/types/Window.h>
#include "ge/graphics/enums/GraphicsApi.h"

namespace ge
{

	struct SimpleEngineCreationInfo
	{
		GraphicsApi::type     g_api;
		WindowConstructorInfo wci;

		std::vector<Runtime*> runtimes;
		std::vector<std::pair<RuntimeGroup*, std::string>> runtime_groups;

		bool addInitPipeline = true;
	};

	void simpleStart(SimpleEngineCreationInfo);
}
