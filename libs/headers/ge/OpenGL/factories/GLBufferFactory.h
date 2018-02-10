//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once

#include <GL/glew.h>
#include <OpenGL/types/GLIndexBuffer.h>

#include <graphics/factories/BufferFactory.h>
#include <graphics/types/VertexBuffer.h>

#include <OpenGL/types/GLVertexBuffer.h>
#include <graphics/types/IndexBuffer.h>


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