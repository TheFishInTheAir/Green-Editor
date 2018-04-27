#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace ge
{
	struct ModelMat
	{

		ModelMat();

		glm::mat4 getMat();

		//glm::mat4 matrix;

		glm::quat rot;
		glm::vec3 pos;
		glm::vec3 scale;

	};
}
