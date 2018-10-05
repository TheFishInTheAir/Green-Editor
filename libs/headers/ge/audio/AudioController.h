#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace ge
{
    namespace Audio
    {
        void standardInit();

        void makeContextCurrent();
        void setListinerPos(glm::vec3);
        void setListinerOrientation(glm::vec3, glm::vec3);
        void setListinerOrientation(glm::quat);
    }
}