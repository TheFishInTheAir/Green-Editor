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

            ge::Error genShader(std::string,ShaderType::type, std::shared_ptr<ge::Shader>*);
            ge::Error genShaderGroup(std::vector<std::shared_ptr<ge::Shader>>, ge::ShaderGroup**);
			void	  destroyShader(ge::Shader*);

        };
    }
}