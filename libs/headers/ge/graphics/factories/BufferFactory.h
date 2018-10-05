//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once

#include <ge/graphics/types/VertexBuffer.h>
#include <ge/graphics/types/IndexBuffer.h>

namespace ge
{
    struct BufferFactory
    {
        virtual ge::VertexBuffer *genVertexBuffer() = 0;

        virtual ge::IndexBuffer  *genIndexBuffer()  = 0;
    };
}