//
// Created by Ethan Breit on 2017-07-27.
//

#pragma once

#include <graphics/types/IndexBuffer.h>
#include <cstddef>
#include <OpenGL/util/EnumUtil.h>
#include <graphics/enums/BufferMemoryType.h>

namespace ge
{
    namespace GL
    {

        struct IndexBuffer : ge::IndexBuffer
        {

            unsigned int id;

            IndexBuffer();

            ~IndexBuffer();

            void bind();

            void bufferData();

        };
    }
}