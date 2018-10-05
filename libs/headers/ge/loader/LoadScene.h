#pragma once
#include <string>
#include <ge/error/Error.h>
#include <ge/graphics/empty_types/Scene.h>


namespace ge
{

	namespace SceneLoader
	{
		Error loadScene(std::string path, Empty::MeshData*);
		Error loadSceneJson(std::string path, Empty::Scene*, bool isResource);
	}
}
