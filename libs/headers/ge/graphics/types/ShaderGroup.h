//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once
#include <vector>
#include <memory>
#include <ge/graphics/types/Shader.h>
#include <ge/graphics/types/Uniform.h>
#include <string>
#include <unordered_map>
namespace ge
{
    struct ShaderGroup
    {
		std::vector<std::shared_ptr<ge::Shader>> shaders; //TODO: MAKE GOOD
        
        std::unordered_map<std::string, ge::Uniform> uniforms;

        virtual ~ShaderGroup()
        {}
    };
}
