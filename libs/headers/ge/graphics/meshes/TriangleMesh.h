//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once

#include <ge/graphics/types/VertexBuffer.h>
#include <ge/graphics/types/Uniform.h>
#include <ge/graphics/types/Texture.h>
#include <ge/graphics/types/ShaderGroup.h>
#include <ge/graphics/types/IndexBuffer.h>
#include <ge/graphics/empty_types/MeshData.h>
#include <ge/graphics/types/CubeMap.h>

namespace ge
{

	struct TriangleMesh //TODO: @REFACTOR to Mesh.  We only support triangle meshes.
    {
        virtual void render() = 0;
        virtual ~TriangleMesh(){};
        bool cullBackface = true;

        virtual void rebuffer() = 0;


        virtual void setShaderGroup(ge::ShaderGroup*) = 0;
        virtual ge::ShaderGroup* getShaderGroup() = 0;

        virtual void setIndexBuffer(ge::IndexBuffer*) = 0;
        virtual ge::IndexBuffer* getIndexBuffer() = 0;

        virtual bool isComplete() = 0;

        virtual void registerUniform(std::string) = 0;
        virtual void registerVertexBuffer(std::string, ge::VertexBuffer*) = 0;
        virtual void registerTexture(ge::Texture*, unsigned int) = 0;
		virtual void registerCubeMap(ge::CubeMap*, unsigned int)  = 0;
        
        virtual bool containsUniform(std::string) = 0;
        
        virtual std::vector<ge::Texture*> getTextures() = 0;

        virtual ge::Uniform* getUniform(std::string) = 0; //Deprecated @DEPRECATED TODO: Deprecate, NOTE: is this enough deprecates?
        virtual ge::VertexBuffer* getVertexBuffer(std::string) = 0;

        virtual void setUniform(std::string, ge::Uniform::UniformContent) = 0;

        virtual void deepDestroy() = 0; //Destroy EVERYTHING, except for the shader and the textures and the cubemaps...

        //TODO: add like a 'virtual void turboDeepUltraDestructionDestroy() = 0;' to destroy literally everything.

    };
}
