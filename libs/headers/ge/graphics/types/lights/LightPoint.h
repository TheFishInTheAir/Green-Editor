#pragma once
#include <glm/glm.hpp>
#include <ge/graphics/meshes/TriangleMesh.h>

namespace ge
{
	struct LightPoint
	{
		glm::vec3 pos;
		glm::vec3 colour;

		float ambient = 0;

		float constant = 1;
		float linear = 0.09;
		float quadratic = 0.032;

		void pushUnifValues(TriangleMesh* mesh, std::string prefix);

	};
}
