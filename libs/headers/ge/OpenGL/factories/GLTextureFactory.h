//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <graphics/factories/TextureFactory.h>

namespace ge
{
    namespace GL
    {
        struct TextureFactory : ge::TextureFactory
        {
	        Error genTexture(Image img, ge::Texture** outTex);
        };
    }
}