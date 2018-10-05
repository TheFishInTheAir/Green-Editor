#pragma once
#include <ge/graphics/empty_types/MeshData.h>
#include <engine/global_settings.pre>

//TODO: Refactor default_geom into the engine folder. NOTE: Should do soon

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

			const ge::Empty::MeshData getMeshData();
		}
	}

}
