#pragma once
#include "Scene.h"
#include <json/json.hpp>
namespace ge
{
    namespace SceneSerializer
    {
        nlohmann::json serializeSceneJson(Scene* s);
        nlohmann::json serializeCurrentSceneJson();
    }
}