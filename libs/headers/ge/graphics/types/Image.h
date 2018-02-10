//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <graphics/enums/ColourModelType.h>

namespace ge
{
    struct Image
    {

        ColourModelType::type model;

        int width, height;

        const void *data;

    };
}