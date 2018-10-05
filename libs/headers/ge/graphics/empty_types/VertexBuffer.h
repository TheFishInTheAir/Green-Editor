#pragma once

#include <ge/graphics/enums/DataType.h>
#include <ge/graphics/enums/BufferMemoryType.h>
#include <stdlib.h>

namespace ge
{
	namespace Empty
	{
		struct VertexBuffer
		{
			unsigned int attributeId;
			int sizePerAttrib;
			void* offset;
			ge::BasicDataType::type dataType;
			bool normalized;

			bool unique = false;


			size_t size;
			const void* data;
			BufferMemoryType::type memoryType;
		};
	}
}
