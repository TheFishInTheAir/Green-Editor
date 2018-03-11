#pragma once
#include "graphics/types/ShaderGroup.h"
#include "graphics/meshes/TriangleMesh.h"
#include <engine/defaults/StaticObject.h>

#include "runtime/Runtime.h"
#include "graphics/Camera.h"
#include "graphics/types/CubeMap.h"


namespace ge
{
	struct GraphicsCore;
	struct Scene;

	struct SkyBox
	{

		SkyBox(CubeMap*);


		SkyBox();

		SkyBox(Scene);

		~SkyBox();

		TriangleMesh* mesh;

		ShaderGroup* shaders;

		CubeMap* cubeMap;

		//std::shared_ptr<Texture> albedo;

		void render();

		void clear();

		ge_START_CYCLE_HANDLER(SkyBox)
			ge_GENERATE_TRAMPOLINE(render, RENDER)
		ge_END_CYCLE_HANDLER

	private:
		Uniform* u_vp;

		Camera* currentCamera;

		void initRenderer();
		//void initTextures(Empty::StaticObject*);

		static GraphicsCore*	_gCore;

		//ge::Scene				_scene;

		//Temporary testing code

		Uniform* u_cubemap;

		void initTest();


	};

	void setSkyBox(std::string);

}
