//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <ge/graphics/factories/TextureFactory.h>

namespace ge
{
    namespace GL
    {
        struct TextureFactory : ge::TextureFactory
        {
	        Error genTexture(Image img, ge::Texture** outTex);
			Error genCubeMap(std::array<Image, 6>, CubeMap**);
            void  genFramebuffer(uint32_t width, uint32_t height, ge::FrameBuffer** outBuf);

        };
    }
}