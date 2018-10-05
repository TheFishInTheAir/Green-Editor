#pragma once
#include "runtime/Runtime.h"
#include <engine/global_settings.pre>
#include "nuklear.h"
#include "graphics/empty_types/Scene.h"
#include "engine/scene/Scene.h"
#include "engine/defaults/StaticObject.h"
#include "debug/debug_entities/ColouredBox.h"


struct StaticObjectWidget
{
	StaticObjectWidget(nk_context*);

	void render();
	void update();
	void postRender();

	ge_START_CYCLE_HANDLER(StaticObjectWidget)
		ge_GENERATE_TRAMPOLINE(update, UPDATE)
		ge_GENERATE_TRAMPOLINE(render, 9)
		ge_GENERATE_TRAMPOLINE(postRender, POST_RENDER)
	ge_END_CYCLE_HANDLER

private:

	void drawObjectGroup();
	void drawTransformData();

	void move(ge::StaticObject*);
	void scale(ge::StaticObject*);
	void rotate(ge::StaticObject*);


	nk_context* ctx;

	std::forward_list<ge::StaticObject*> *objs = nullptr;

	int selected = -1;

	int count = -1;

	int translationMode = 0;

	nk_size moveScale = 1*100;


	ge::Debug::DebugColouredBox* box = nullptr;
};
