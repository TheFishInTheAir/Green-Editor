#pragma once
#include "runtime/Runtime.h"
#include <engine/global_settings.pre>
#include "nuklear.h"
#include "graphics/empty_types/Scene.h"
#include "engine/scene/Scene.h"

struct SceneWiget
{
	SceneWiget(nk_context*);

	void render();
	void update();

	void saveScene();

	ge_START_CYCLE_HANDLER(SceneWiget)
		ge_GENERATE_TRAMPOLINE(update, UPDATE)
		ge_GENERATE_TRAMPOLINE(render, 9)
		ge_END_CYCLE_HANDLER

private:
	nk_context *ctx;


	std::string scenePath;
	int scenePathState;
	ge::Empty::Scene sceneTemplate;
	ge::Scene *scene;

	bool shouldLoad = false;
};
