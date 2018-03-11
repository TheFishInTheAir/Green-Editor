//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once

#include <graphics/types/VertexBuffer.h>
#include <graphics/types/Uniform.h>
#include <graphics/types/Texture.h>
#include "graphics/types/ShaderGroup.h"
#include "graphics/types/IndexBuffer.h"
#include "graphics/empty_types/MeshData.h"
#include "graphics/types/CubeMap.h"

namespace ge
{

	struct TriangleMesh
    {
        virtual void render() = 0;
        virtual ~TriangleMesh(){};

        virtual void rebuffer() = 0;


        virtual void setShaderGroup(ge::ShaderGroup*) = 0;
        virtual ge::ShaderGroup* getShaderGroup() = 0;

        virtual void setIndexBuffer(ge::IndexBuffer*) = 0;
        virtual ge::IndexBuffer* getIndexBuffer() = 0;


        virtual void registerUniform(std::string) = 0;
        virtual void registerVertexBuffer(std::string, ge::VertexBuffer*) = 0;
        virtual void registerTexture(ge::Texture*, unsigned int) = 0;
		virtual void registerCubeMap(ge::CubeMap*, unsigned int)  = 0;

        virtual ge::Uniform* getUniform(std::string) = 0;
        virtual ge::VertexBuffer* getVertexBuffer(std::string) = 0;


    };
}
