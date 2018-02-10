#pragma once
#include <engine/global_settings.pre>
#include "runtime/Runtime.h"
#include "runtime/GlobalRuntime.h"
#include <graphics/GraphicsCore.h>
#include <memory/GlobalMemory.h>

struct ui
{
<<<<<<< Updated upstream
	ui();

	void preRender();
	void render();
	void postRender();

	void update();
	static void init();

	ge_START_CYCLE_HANDLER(ui)
		ge_GENERATE_TRAMPOLINE(update, UPDATE)

		ge_GENERATE_TRAMPOLINE(preRender,	8)
		ge_GENERATE_TRAMPOLINE(render,		9)
		ge_GENERATE_TRAMPOLINE(postRender,	10)

=======
	void render();
	void update();
	static void init();
	ge_START_CYCLE_HANDLER(ui)
		ge_GENERATE_TRAMPOLINE(update, UPDATE)
		ge_GENERATE_TRAMPOLINE(render, POST_RENDER)
>>>>>>> Stashed changes
	ge_END_CYCLE_HANDLER

private:

	static ge::GraphicsCore* gc;
<<<<<<< Updated upstream

	int *state;
	std::string *value;

=======
>>>>>>> Stashed changes
};