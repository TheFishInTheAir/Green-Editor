#pragma once
#include <ge/graphics/types/Material.h>
namespace ge
{
    namespace MaterialLoader
    {
        Material loadMaterial(std::string url, bool isResource);
    }
}