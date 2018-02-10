#pragma once
#include "Light.h"

namespace ge
{
	struct LightSpot : Light
	{
		glm::vec3 dir;
		float coneAngle;

		LightType::type getLightType()
		{
			return LightType::Point;
		}
	};
}
