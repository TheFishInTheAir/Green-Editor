//
// Created by Ethan Breit on 2017-07-27.
//

#pragma once

#include <graphics/enums/BufferMemoryType.h>
#include <cstddef>
#include "graphics/empty_types/IndexBuffer.h"

namespace ge
{
    struct IndexBuffer
    {
        virtual ~IndexBuffer(){}
        

		Empty::IndexBuffer* data;

        virtual void bufferData() = 0;
    };
}
