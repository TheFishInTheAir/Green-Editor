//
// Created by Ethan Breit on 2017-07-08.
//

#pragma once

#include <glm/glm.hpp>
#include <ge/graphics/Camera.h>
namespace ge
{

    struct FreeMove
    {
        void update(Camera *);


        float _verticalAngle    = 0.0f;
        float _horizontalAngle  = 0.0f;
        glm::vec3 _position;

        float speed;

        float lookSpeed;
    };

}