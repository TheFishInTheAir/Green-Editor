//
// Created by Ethan Breit on 2017-07-26.
//

#pragma once
#include <string>
#include <ge/graphics/meshes/TriangleMesh.h>
#include <ge/graphics/abs/OpenGL/types/GLTexture.h>
#include <ge/graphics/abs/OpenGL/types/GLVertexBuffer.h>
#include <ge/graphics/abs/OpenGL/types/GLUniform.h>
#include <ge/graphics/abs/OpenGL/types/GLShaderGroup.h>
#include <ge/graphics/abs/OpenGL/types/GLIndexBuffer.h>
#include <ge/graphics/abs/OpenGL/types/GLCubeMap.h>

namespace ge
{
    namespace GL
    {
        struct TriangleMesh : ge::TriangleMesh
        {
            GL::ShaderGroup* shaderGroup = nullptr;
            GL::IndexBuffer* indexBuffer = nullptr;

	        void startRender();

			bool isRendering = false;

            TriangleMesh();
            ~TriangleMesh();

            void render();

            void rebuffer();
            
            bool isComplete();

            void setIndexBuffer(ge::IndexBuffer*);
            ge::IndexBuffer* getIndexBuffer();

            void setShaderGroup(ge::ShaderGroup*);
            ge::ShaderGroup* getShaderGroup();

            void registerUniform(std::string);

            void registerVertexBuffer(std::string, ge::VertexBuffer *);

            void registerTexture(ge::Texture*, unsigned int);

			void registerCubeMap(ge::CubeMap*, unsigned int);

            std::vector<ge::Texture*> getTextures();
            
            ge::Uniform* getUniform(std::string);
            
            void setUniform(std::string, ge::Uniform::UniformContent);
            
            bool containsUniform(std::string);

            ge::VertexBuffer *getVertexBuffer(std::string);


            void deepDestroy();
        private:
            
            void applyUniform(ge::Uniform&);
            
            unsigned int _vao;

            std::map<unsigned int, ge::GL::Texture*> _textures;
			std::map<unsigned int, ge::GL::CubeMap*> _cMaps;

            std::map<std::string,ge::GL::VertexBuffer*> _vertexBuffers;
            std::map<std::string,ge::GL::Uniform*> _uniforms;

        };
    }
}
