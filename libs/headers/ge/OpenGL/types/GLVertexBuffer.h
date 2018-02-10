//
// Created by Ethan Breit on 2017-07-25.
//

#pragma once
#include <GL/glew.h>

#include <graphics/enums/DataType.h>
#include <graphics/types/VertexBuffer.h>

#include <OpenGL/util/EnumUtil.h>

namespace ge
{
    namespace GL
    {

        struct VertexBuffer : ge::VertexBuffer
        {
            unsigned int id;

            VertexBuffer();
            ~VertexBuffer();

            void bind();

            void bufferData();

        };
    }
}