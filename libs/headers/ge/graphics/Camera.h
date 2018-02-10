//
// Created by Ethan Breit on 2017-08-07.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace ge
{

    struct Camera
    {

        void update();

        glm::vec3 pos;
        glm::vec3 dir;
        glm::vec3 up;

        glm::mat4 view;
        glm::mat4 proj;

        glm::mat4 vp;

        float nearCull;
        float farCull;

        float aspectRatio;

        float fov;

    };

}