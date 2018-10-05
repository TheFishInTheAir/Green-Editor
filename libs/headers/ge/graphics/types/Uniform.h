//
// Created by Ethan Breit on 2017-07-25.
//

#pragma once

#include <glm/glm.hpp>

namespace ge
{
    struct Uniform //@DEPRECATED? maybe
    {
        //TODO: PUT ENUM IN DIFFERENT FILE
        
        typedef enum
        {
            FLOAT,
            INT,
            
            FVEC2,
            FVEC3,
            FVEC4,
            MAT2,
            MAT3,
            MAT4
            
            
        } UniformType;
        
        union UniformContent
        {
            float       fv1;
            
            glm::vec2        fv2;
            glm::vec3        fv3;
            glm::vec4        fv4;
            
            glm::mat2        fm2;
            glm::mat3        fm3;
            glm::mat4        fm4;
            
            int32_t    iv1;
            
            UniformContent(){};
            
            UniformContent(float f)       : fv1(f) {};
            UniformContent(int   i)       : iv1(i) {};
            
            UniformContent(glm::vec2 f)   : fv2(f) {};
            UniformContent(glm::vec3 f)   : fv3(f) {};
            UniformContent(glm::vec4 f)   : fv4(f) {};
            
            UniformContent(glm::mat2 f)   : fm2(f) {};
            UniformContent(glm::mat3 f)   : fm3(f) {};
            UniformContent(glm::mat4 f)   : fm4(f) {};
            
            
        };
        
        Uniform(UniformType);
        
        uint32_t descriptorId = 0;
        
        
        
        union //TODO: REMOVE AND REFACTOR i.e. UniformContent content; and delete this
        {
            float       fv1;
            
            glm::vec2        fv2;
            glm::vec3        fv3;
            glm::vec4        fv4;
            
            glm::mat2        fm2;
            glm::mat3        fm3;
            glm::mat4        fm4;
            
            int32_t    iv1;
            /*glm::tvec2<int32_t> iv2;
            glm::tvec3<int32_t> iv3;
            glm::tvec4<int32_t> iv4;*/
        };
        
        UniformType getUniformType();
        
    private:
        UniformType type;
        
        
        
        /*
        
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
        */
        /*
        virtual void setData(uint32_t)               = 0;
        virtual void setData(glm::tvec2<uint32_t>)   = 0;
        virtual void setData(glm::tvec3<uint32_t>)   = 0;
        virtual void setData(glm::tvec4<uint32_t>)   = 0;
        */
        
        /*
        virtual void setData(double)               = 0;
        virtual void setData(glm::tvec2<double>)   = 0;
        virtual void setData(glm::tvec3<double>)   = 0;
        virtual void setData(glm::tvec4<double>)   = 0;*/
    };
}
