//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once

#include <GL/glew.h>
#include <ge/graphics/abs/OpenGL/types/GLIndexBuffer.h>

#include <ge/graphics/factories/BufferFactory.h>
#include <ge/graphics/types/VertexBuffer.h>

#include <ge/graphics/abs/OpenGL/types/GLVertexBuffer.h>
#include <ge/graphics/types/IndexBuffer.h>


namespace ge
{
    namespace GL
    {
        struct BufferFactory : ge::BufferFactory
        {
            ge::VertexBuffer *genVertexBuffer();

            ge::IndexBuffer  *genIndexBuffer();
        };
    }
}