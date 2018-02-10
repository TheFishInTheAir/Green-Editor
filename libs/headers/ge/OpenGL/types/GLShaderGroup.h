//
// Created by Ethan Breit on 2017-07-23.
//

#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>
#include <error/Error.h>
#include "GLShader.h"
#include "GLVertexBuffer.h"
#include "GLUniform.h"

#include <graphics/types/ShaderGroup.h>



namespace ge
{
    namespace GL
    {
        struct ShaderGroup : ge::ShaderGroup
        {
            ~ShaderGroup();

            GLuint programID;

        };
    }
}