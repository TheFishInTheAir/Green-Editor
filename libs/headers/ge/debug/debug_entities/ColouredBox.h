#pragma once
#include "graphics/types/Uniform.h"
#include "graphics/Camera.h"
#include "util/PreprocessorUtil.h"

#include "runtime/Runtime.h"
#include <engine/global_settings.pre>
#include "graphics/meshes/TriangleMesh.h"

namespace ge
{
	namespace Debug {

		struct DebugColouredBox
		{

			DebugColouredBox(Camera*);
			DebugColouredBox(Camera* camera, glm::vec3 pos);


			glm::vec3 colour;
			glm::mat4 model = glm::mat4(1);

			Uniform* mvp_u;
			Uniform* colour_u;


			Camera* camera;

			void render();

			ge_START_CYCLE_HANDLER(DebugColouredBox)
				ge_GENERATE_TRAMPOLINE(render, RENDER)
			ge_END_CYCLE_HANDLER

			//Graphics Data
			TriangleMesh* mesh;
			bool initialised = false;

		};

	}
}
