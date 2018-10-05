//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <ge/graphics/factories/ShaderFactory.h>
#include <ge/graphics/types/Window.h>
#include <ge/graphics/factories/BufferFactory.h>
#include <ge/graphics/factories/MeshFactory.h>
#include <ge/graphics/enums/GraphicsApi.h>

///OpenGL
#include <ge/graphics/abs/OpenGL/types/GLWindow.h>
#include <ge/graphics/abs/OpenGL/factories/GLBufferFactory.h>
#include <ge/graphics/abs/OpenGL/factories/GLShaderFactory.h>
#include <ge/graphics/abs/OpenGL/factories/GLMeshFactory.h>
#include <map>
#include <ge/graphics/factories/TextureFactory.h>
#include <ge/graphics/pipeline/Pipeline.h>

///Vulkan

///Metal
namespace ge
{
    struct GraphicsCore
    {
		static GraphicsCore* ctx;

        GraphicsCore(GraphicsApi::type);

        ShaderFactory       *shaderFactory;
        BufferFactory       *bufferFactory;
        MeshFactory         *meshFactory;
		TextureFactory		*textureFactory;
        Pipeline            *currentPipeline;

        Window              *window;

        bool getSupportedFeature(unsigned int feature);

        std::map<unsigned int, bool> supportedFeatures;

    private:
	    static void staticInit();
    };
}