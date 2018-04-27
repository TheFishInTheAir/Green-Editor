#pragma once
#include "glm/glm.hpp"
#include "graphics/enums/LightType.h"

namespace ge
{
	struct Light
	{
		//Global:
				
		glm::vec3 pos;

		glm::vec3 colour;
		float intensity; ///Implement soon

		virtual LightType::type getLightType() = 0;

		//TODO: add more parameters. @UNFINISHED

	};
}
