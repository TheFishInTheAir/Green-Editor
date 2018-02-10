//
// Created by Ethan Breit on 2017-07-25.
//

#pragma once

#include <glm/glm.hpp>

namespace ge
{
    struct Uniform
    {
        virtual void setData(float)             = 0;
        virtual void setData(glm::vec2)         = 0;
        virtual void setData(glm::vec3)         = 0;
        virtual void setData(glm::vec4)         = 0;

        virtual void setData(glm::mat2)         = 0;
        virtual void setData(glm::mat3)         = 0;
        virtual void setData(glm::mat4)         = 0;

        virtual void setData(int32_t)               = 0;
        virtual void setData(glm::tvec2<int32_t>)   = 0;
        virtual void setData(glm::tvec3<int32_t>)   = 0;
        virtual void setData(glm::tvec4<int32_t>)   = 0;

        /*
        virtual void setData(uint32_t)               = 0;
        virtual void setData(glm::tvec2<uint32_t>)   = 0;
        virtual void setData(glm::tvec3<uint32_t>)   = 0;
        virtual void setData(glm::tvec4<uint32_t>)   = 0;
        */

        virtual void setData(double)               = 0;
        virtual void setData(glm::tvec2<double>)   = 0;
        virtual void setData(glm::tvec3<double>)   = 0;
        virtual void setData(glm::tvec4<double>)   = 0;
    };
}