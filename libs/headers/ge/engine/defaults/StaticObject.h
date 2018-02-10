#pragma once
#include "engine/types/ModelMat.h"
#include "engine/empty_types/EmptyStaticObject.h"

#include "engine/global_settings.pre"
#include "graphics/meshes/TriangleMesh.h"
#include <memory>
#include "runtime/Runtime.h"
#include "graphics/Camera.h"
#include "graphics/types/lights/LightDirectional.h"
#include "graphics/GraphicsCore.h"

//TODO: fix textures, we don't need each Texture passed to us seperatly

namespace ge
{
	struct Scene;

	struct StaticObject
	{

		StaticObject(Empty::StaticObject);

		StaticObject(Empty::StaticObject, Scene);

		~StaticObject();

		ModelMat model;

		TriangleMesh* mesh;

		ShaderGroup* shaders;


		Texture* albedo;

		//std::shared_ptr<Texture> albedo;
		std::shared_ptr<Texture> specular;
		std::shared_ptr<Texture> normal;
		std::shared_ptr<Texture> roughness;

		void render();

		void clear();

		ge_START_CYCLE_HANDLER(StaticObject)
			ge_GENERATE_TRAMPOLINE(render, RENDER)
		ge_END_CYCLE_HANDLER

	private:

		Uniform* u_model;
		Uniform* u_vp;
		Uniform* u_camPos;

		Camera* currentCamera;
		
		void initRenderer();
		void initTextures(Empty::StaticObject*);

		static GraphicsCore* _gCore;


		//Temporary testing code

		Uniform* u_albedo;
		Uniform* u_specular;

		Uniform* u_testlight_col;
		Uniform* u_testlight_dir;
		
		LightDirectional* testlight;

		void initTest();


	};
}
