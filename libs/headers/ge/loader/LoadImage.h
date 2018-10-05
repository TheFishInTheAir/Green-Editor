//
// Created by Ethan Breit on 2017-08-16.
//

#pragma once

#include <ge/error/Error.h>
#include <ge/graphics/types/Image.h>
#include <memory>
#include <ge/game/scene/Scene.h>

namespace ge
{
    namespace ImageLoader
    {
        Error loadImage(std::string, Image**);
		Error loadImage(std::string, std::shared_ptr<Image>*);
		//Error loadImage(std::string, std::shared_ptr<Image>*, Scene*);
    }
}
