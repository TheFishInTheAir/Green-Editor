//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once
#include <gl/glew.h>

#include <graphics/enums/ShaderType.h>
#include <graphics/enums/BufferMemoryType.h>
#include <graphics/enums/DataType.h>

namespace ge
{
    namespace GL
    {
        namespace EnumUtil
        {
            unsigned int getTrueShaderType(ge::ShaderType::type);
            unsigned int getTrueBufferMemoryType(ge::BufferMemoryType::type);
            unsigned int getTrueDataType(ge::DataType::type);
        }
    }
}