#pragma once
#include <string>
#include "error/Error.h"
#include <graphics/empty_types/Scene.h>


namespace ge
{

	namespace SceneLoader
	{
		Error loadScene(std::string path, Empty::MeshData*);
		Error loadSceneJson(std::string path, Empty::Scene*, bool isResource);
	}
}
