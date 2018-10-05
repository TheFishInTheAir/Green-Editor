//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <ge/graphics/enums/TextureFilterType.h>
#include <ge/graphics/enums/ColourModelType.h>
#include <ge/graphics/types/Texture.h>
#include <ge/error/Error.h>
#include <ge/graphics/types/CubeMap.h>

namespace ge
{
    namespace GL
    {

        struct CubeMap : ge::CubeMap
        {
            unsigned int id;


            ge::Error setFiltering(TextureFilterType::type);



        };


    }

}
