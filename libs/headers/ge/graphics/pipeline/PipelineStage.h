#pragma once
#include <ge/graphics/types/ShaderGroup.h>
#include <ge/graphics/Camera.h>
#include <ge/graphics/types/FrameBuffer.h>
#include "PipelineDrawType.h"
namespace ge
{
    struct PipelineStage
    {
        FrameBuffer* framebuffer = nullptr;

        bool overrideShader = false;
        ShaderGroup* overrideSG;

        bool overrideCamera = false;
        Camera* cam;
        
        PipelineDrawType::type type; //i.e. gui, post-processing, etc...
    };
}