//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once
#include <string>
#include <graphics/meshes/TriangleMesh.h>
#include <OpenGL/types/GLTexture.h>
#include "OpenGL/types/GLVertexBuffer.h"
#include "OpenGL/types/GLUniform.h"
#include "OpenGL/types/GLShaderGroup.h"
#include "OpenGL/types/GLIndexBuffer.h"

namespace ge
{
    namespace GL
    {
        struct TriangleMesh : ge::TriangleMesh
        {
            GL::ShaderGroup* shaderGroup;
            GL::IndexBuffer* indexBuffer;

			void startRender();

			bool isRendering = false;

            TriangleMesh();
            ~TriangleMesh();

            void render();

            void rebuffer();

            void setIndexBuffer(ge::IndexBuffer*);
            ge::IndexBuffer* getIndexBuffer();

            void setShaderGroup(ge::ShaderGroup*);
            ge::ShaderGroup* getShaderGroup();

            void registerUniform(std::string);

            void registerVertexBuffer(std::string, ge::VertexBuffer *);

            void registerTexture(ge::Texture*, unsigned int);

            ge::Uniform* getUniform(std::string);

            ge::VertexBuffer *getVertexBuffer(std::string);
        private:

            unsigned int _vao;

            std::map<unsigned int, ge::GL::Texture*> _textures;
            std::map<std::string,ge::GL::VertexBuffer*> _vertexBuffers;
            std::map<std::string,ge::GL::Uniform*> _uniforms;

        };
    }
}