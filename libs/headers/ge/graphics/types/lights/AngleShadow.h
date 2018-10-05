#pragma once
#include <glm/glm.hpp>
#include <ge/graphics/types/Texture.h>

namespace ge
{
	struct AngleShadow
	{
        Texture* shadowMap;
        glm::mat4 lightSpace;
	};
}
