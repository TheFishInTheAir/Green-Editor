#pragma once
#include "Light.h"

namespace ge
{
	struct LightPoint : Light
	{

		LightType::type getLightType()
		{
			return LightType::Point;
		}

	};
}
