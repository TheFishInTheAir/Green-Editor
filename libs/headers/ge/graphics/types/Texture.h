//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <ge/graphics/enums/TextureFilterType.h>
#include <ge/graphics/enums/ColourModelType.h>
#include <ge/error/Error.h>

namespace ge
{
    struct Texture
    {
        //NOTE: we should maybe have a thing here for the name/url
        std::string url;
        
        int getWidth() const;
        int getHeight() const;

        TextureFilterType::type getFiltering();
        ColourModelType::type getColourModel();
        virtual Error setFiltering(TextureFilterType::type) = 0;

    private:
        int width,height;

        TextureFilterType   ::type filtering;
        ColourModelType     ::type colourModel;

    };
}
