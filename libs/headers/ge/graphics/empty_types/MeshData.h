#pragma once
#include <vector>
#include "graphics/types/VertexBuffer.h"
#include "graphics/types/Texture.h"
#include "graphics/types/ShaderGroup.h"
#include "graphics/types/IndexBuffer.h"

namespace ge
{
	namespace Empty
	{
		struct MeshData
		{
			typedef std::pair<VertexBuffer*, std::string> vertBuf;
			typedef std::pair<Texture*, unsigned int> tex;


			std::vector<vertBuf>	vertexBuffers;
			std::vector<tex>		Textures;
			ShaderGroup* shaderGroup;
			IndexBuffer* indexBuffer;

			bool hasShaderGroup = false;
			bool hasIndexBuffer = false;

		};
	}
}
