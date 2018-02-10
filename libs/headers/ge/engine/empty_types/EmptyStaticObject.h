#pragma once
#include "engine/types/ModelMat.h"
#include <string>
#include "graphics/empty_types/MeshData.h"

namespace ge
{
	namespace Empty
	{
		struct StaticObject
		{
			ModelMat model;

			std::string mesh;

			std::string lighting_type;
			std::string custom_shader;
			std::string albedo;
			std::string specular;
			std::string normal;
			std::string roughness;

			bool override_tex;
			float uvscale;
		};
	}
}
