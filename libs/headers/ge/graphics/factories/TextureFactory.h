//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <ge/error/Error.h>
#include <ge/graphics/types/Image.h>
#include <ge/graphics/types/Texture.h>
#include <ge/graphics/types/CubeMap.h>
#include <ge/graphics/types/FrameBuffer.h>

namespace ge
{
    struct TextureFactory
    {
        virtual Error genTexture(Image, Texture**)     = 0;
		virtual Error genCubeMap(std::array<Image, 6>, CubeMap**) = 0;
        virtual void  genFramebuffer(uint32_t width, uint32_t height, ge::FrameBuffer** outBuf) = 0;

    };
}
