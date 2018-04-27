#pragma once
#include "graphics/empty_types/MeshData.h"
#include <engine/global_settings.pre>

namespace ge
{
	namespace dgeo
	{
		namespace cube
		{
			
			const float vertecies[] =
			{
				-0.5f,-0.5f,-0.5f, // triangle 1 : begin
				-0.5f,-0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f, // triangle 1 : end
				0.5f, 0.5f,-0.5f, // triangle 2 : begin
				-0.5f,-0.5f,-0.5f,
				-0.5f, 0.5f,-0.5f, // triangle 2 : end
				0.5f,-0.5f, 0.5f,
				-0.5f,-0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f, 0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				-0.5f,-0.5f,-0.5f,
				-0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f,-0.5f,
				0.5f,-0.5f, 0.5f,
				-0.5f,-0.5f, 0.5f,
				-0.5f,-0.5f,-0.5f,
				-0.5f, 0.5f, 0.5f,
				-0.5f,-0.5f, 0.5f,
				0.5f,-0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f, 0.5f,-0.5f,
				0.5f,-0.5f,-0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f,-0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f, 0.5f,-0.5f,
				-0.5f, 0.5f,-0.5f,
				0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f,-0.5f,
				-0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f,
				0.5f,-0.5f, 0.5f
			};

			const int indicies[] =
			{
				0,
				1,
				2,
				3,
				4,
				5,
				6,
				7,
				8,
				9,
				10,
				11,
				12,
				13,
				14,
				15,
				16,
				17,
				18,
				19,
				20,
				21,
				22,
				23,
				24,
				25,
				26,
				27,
				28,
				29,
				30,
				31,
				32,
				33,
				34,
				35
			};

			const ge::Empty::MeshData getMeshData()
			{
				static ge::Empty::MeshData data;

				static bool first = true;
				if(first)
				{
					first = false;
					data.hasIndexBuffer = true;
					data.hasShaderGroup = false;
					ge::Empty::IndexBuffer* i = new ge::Empty::IndexBuffer();
					i->data = &indicies;
					i->memoryType = ge::BufferMemoryType::Static;
					i->length = 36;
					i->size = sizeof(int) * 36;

					ge::Empty::VertexBuffer* v = new ge::Empty::VertexBuffer();
					v->data = &vertecies;
					v->attributeId = VERTEX_POSITION;
					v->dataType = DataType::Float;
					v->memoryType = BufferMemoryType::Static;
					v->normalized = false;
					v->size = 3 * 36 * sizeof(float);
					v->offset = 0;
					v->sizePerAttrib = 3;


					data.indexBuffer = i;
					data.vertexBuffers.push_back({ v, "vertex" });

				}
				return data;

			}

		}
	}

}
