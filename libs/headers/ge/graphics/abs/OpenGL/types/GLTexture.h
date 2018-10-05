//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <ge/graphics/enums/TextureFilterType.h>
#include <ge/graphics/enums/ColourModelType.h>
#include <ge/graphics/types/Texture.h>
#include <ge/error/Error.h>

namespace ge
{
    namespace GL
    {

        struct Texture : ge::Texture
        {
            unsigned int id;


			ge::Error setFiltering(TextureFilterType::type);

        };


    }

}