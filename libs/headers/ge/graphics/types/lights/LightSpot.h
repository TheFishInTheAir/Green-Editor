#pragma once
#include <glm/glm.hpp>
#include <ge/graphics/meshes/TriangleMesh.h>

namespace ge
{
	struct LightSpot
	{
		glm::vec3 pos;
		glm::vec3 dir;
		glm::vec3 colour;

		float ambient = 0;
		
		float angle = 45;
		float outerAngle = 15;

		int shadowLoc = -1;

		void pushUnifValues(TriangleMesh* mesh, std::string prefix);
	};
}
