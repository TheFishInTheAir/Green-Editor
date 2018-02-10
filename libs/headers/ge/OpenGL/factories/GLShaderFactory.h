//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <GL/glew.h>

#include <graphics/factories/ShaderFactory.h>

namespace ge
{
    namespace GL
    {
        struct ShaderFactory : public ge::ShaderFactory
        {

            ge::Error genShader(std::string,ShaderType::type, ge::Shader**);
            ge::Error genShaderGroup(std::vector<ge::Shader*>, ge::ShaderGroup**);

        };
    }
}