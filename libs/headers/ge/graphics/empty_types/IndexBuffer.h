//
// Created by Ethan Breit on 2017-07-27.
//

#pragma once

#include <graphics/enums/BufferMemoryType.h>
#include <cstddef>

namespace ge
{
	namespace Empty
	{
		struct IndexBuffer
		{
			unsigned int length;

			size_t size;
			const void* data;
			BufferMemoryType::type memoryType;

		};
	}
}