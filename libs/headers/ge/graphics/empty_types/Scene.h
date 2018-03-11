#pragma once

#include <forward_list>
#include "graphics/types/Texture.h"
#include "graphics/empty_types/MeshData.h"
#include "graphics/types/Shader.h"
#include <memory>
#include "graphics/types/Image.h"
#include <unordered_map>
#include "engine/empty_types/EmptyStaticObject.h"
#include <array>

namespace ge
{
	namespace Empty
	{

		struct Scene //TODO: think before writing
		{

			//TODO: First get Textures working and then get the others going.

			std::vector<std::string>								keptRes;

			std::unordered_map<std::string, ge::Image>				images;
			std::unordered_map<std::string, ge::Empty::MeshData>	meshes;
			std::unordered_map<std::string, std::array<ge::Image, 6>>		cubemaps;


			std::forward_list<std::string>							shaders;


			std::forward_list<Empty::StaticObject>					staticObjects;


			std::string	skybox = "";

			//std::map<std::string, std::shared_ptr<ge::Empty::MeshData>> meshs;
			//std::map<std::string, std::shared_ptr<ge::Shader>> shaders;
			//std::map<std::string, std::shared_ptr<ge::ShaderGroup>> shaderGroups;

			//TODO: create light class/struct 

			//std::vector<Light> lights;

		};
	}
}
