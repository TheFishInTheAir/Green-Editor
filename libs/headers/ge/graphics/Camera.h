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
        
        static Camera* displayCamera;

        void update();

        glm::vec3 pos = glm::vec3(0);
        glm::vec3 dir = glm::vec3(0,0,-1);
        glm::vec3 up  = glm::vec3(0,1,0);;

        glm::mat4 view;
        glm::mat4 proj;

        glm::mat4 vp;

        float nearCull = 0.01f;
        float farCull = 100;

        float aspectRatio = 1920.0f/1080;

        float fov = glm::radians(45.0f);

    };

}
