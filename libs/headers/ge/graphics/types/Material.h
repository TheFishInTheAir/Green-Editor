#pragma once
#include <vector>
#include <cstdint>
#include <ge/graphics/types/Uniform.h>
#include <string>
namespace ge
{
    struct Material
    {
        std::string name = "NULL";
        std::string url = "";

        std::string shader_group = "NULL";
                            //display tag           tex URL       tex slot
        std::vector<std::pair<std::string, std::pair<std::string, uint32_t>>> textures;
        std::vector<std::pair<std::string, std::pair<std::string, uint32_t>>> cubemaps;

        std::vector<std::pair<std::string, std::pair<std::string, Uniform::UniformContent>>> uniform_values;
    };
}