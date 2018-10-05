#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>


namespace ge
{
    namespace Debug
    {
        namespace DebugBox
        {
            void draw(glm::vec3, glm::vec3, glm::vec3, glm::quat, glm::mat4);

            void draw(glm::vec3, glm::vec3, glm::vec3, glm::mat4);
            void draw(glm::vec3, glm::vec3, glm::vec3);
            void draw(glm::vec3, glm::vec3, glm::vec3, glm::quat);
            void draw2(glm::vec3, glm::vec3, glm::vec3, glm::quat);

        }
    }
}