//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once
#include <GL/glew.h>
#include <ge/graphics/types/Shader.h>

namespace ge
{
    namespace GL
    {

        struct Shader : ge::Shader
        {

            unsigned int id;
        };
    }
}