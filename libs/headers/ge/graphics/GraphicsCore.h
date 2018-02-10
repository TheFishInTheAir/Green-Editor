//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <graphics/factories/ShaderFactory.h>
#include <graphics/types/Window.h>
#include <graphics/factories/BufferFactory.h>
#include <graphics/factories/MeshFactory.h>
#include <graphics/enums/GraphicsApi.h>

///OpenGL
#include <OpenGL/types/GLWindow.h>
#include <OpenGL/factories/GLBufferFactory.h>
#include <OpenGL/factories/GLShaderFactory.h>
#include <OpenGL/factories/GLMeshFactory.h>
#include <map>
#include "factories/TextureFactory.h"

///Vulkan

///Metal
namespace ge
{
    struct GraphicsCore
    {

        GraphicsCore(GraphicsApi::type);

        ShaderFactory       *shaderFactory;
        BufferFactory       *bufferFactory;
        MeshFactory         *meshFactory;
		TextureFactory		*textureFactory;

        Window              *window;

        bool getSupportedFeature(unsigned int feature);

        std::map<unsigned int, bool> supportedFeatures;
    };
}