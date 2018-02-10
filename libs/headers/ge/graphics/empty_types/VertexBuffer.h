#pragma once

#include <graphics/enums/DataType.h>
#include <graphics/enums/BufferMemoryType.h>

namespace ge
{
	namespace Empty
	{
		struct VertexBuffer
		{
			unsigned int attributeId;
			int sizePerAttrib;
			void* offset;
			ge::DataType::type dataType;
			bool normalized;

			bool unique = false;


			size_t size;
			const void* data;
			BufferMemoryType::type memoryType;
		};
	}
}
