#pragma once
#include <glm/glm.hpp>
namespace ge
{
	struct AABB2D
	{
		glm::vec2 center;
		glm::vec2 extents;

		AABB2D(glm::vec2, glm::vec2);

		bool collidesWith(AABB2D);

		bool inside(glm::vec2);
	};
}