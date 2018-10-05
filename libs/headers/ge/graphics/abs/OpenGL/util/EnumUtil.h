//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once
#include <GL/glew.h>

#include <ge/graphics/enums/ShaderType.h>
#include <ge/graphics/enums/BufferMemoryType.h>
#include <ge/graphics/enums/DataType.h>

namespace ge
{
    namespace GL
    {
        namespace EnumUtil
        {
            unsigned int getTrueShaderType(ge::ShaderType::type);
            unsigned int getTrueBufferMemoryType(ge::BufferMemoryType::type);
            unsigned int getTrueDataType(ge::BasicDataType::type);
        }
    }
}
