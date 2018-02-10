//
// Created by Ethan Breit on 2017-07-08.
//

#pragma once


#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <math.h>


namespace ge
{
    namespace RotationUtil
    {

        glm::vec3 getDirection(float verticalAngle, float horizontalAngle);
        glm::vec3 getRight(float horizontalAngle);
    }
}


