//
// Created by Ethan Breit on 2017-07-25.
//

#pragma once

#include <graphics/enums/DataType.h>
#include <graphics/enums/BufferMemoryType.h>
#include "graphics/empty_types/VertexBuffer.h"

namespace ge
{
    struct VertexBuffer
    {

        virtual ~VertexBuffer(){}

		Empty::VertexBuffer* data;

        virtual void bufferData() = 0;

    };
}
