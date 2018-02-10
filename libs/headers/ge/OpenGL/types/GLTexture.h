//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <graphics/enums/TextureFilterType.h>
#include <graphics/enums/ColourModelType.h>
#include <graphics/types/Texture.h>
#include <error/Error.h>

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