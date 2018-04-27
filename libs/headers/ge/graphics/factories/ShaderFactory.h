//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <string>
#include <graphics/types/Shader.h>
#include <graphics/enums/ShaderType.h>
#include <error/Error.h>
#include <graphics/types/ShaderGroup.h>
#include <memory>

namespace ge
{
    struct ShaderFactory
    {
        virtual Error genShader(std::string,ShaderType::type, std::shared_ptr<ge::Shader>*)     = 0;
        virtual Error genShaderGroup(std::vector<std::shared_ptr<ge::Shader>>, ShaderGroup**)   = 0;
		virtual void  destroyShader(ge::Shader*)												= 0;
    };
}