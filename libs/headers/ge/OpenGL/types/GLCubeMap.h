//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <graphics/enums/TextureFilterType.h>
#include <graphics/enums/ColourModelType.h>
#include <graphics/types/Texture.h>
#include <error/Error.h>
#include "graphics/types/CubeMap.h"

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
