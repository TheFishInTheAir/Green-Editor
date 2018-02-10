#pragma once
#include <engine/global_settings.pre>
#include "runtime/Runtime.h"
#include "runtime/GlobalRuntime.h"
#include <graphics/GraphicsCore.h>

struct Core
{
	Core();

	void update();
	void prerender();
<<<<<<< Updated upstream
	void finalRender();

	ge_START_CYCLE_HANDLER(Core)
		ge_GENERATE_TRAMPOLINE(update,		UPDATE)
		ge_GENERATE_TRAMPOLINE(prerender,	PRE_RENDER)
		ge_GENERATE_TRAMPOLINE(finalRender,	12)
=======
	void postrender();

	ge_START_CYCLE_HANDLER(Core)
	ge_GENERATE_TRAMPOLINE(update,		UPDATE)
	ge_GENERATE_TRAMPOLINE(prerender,	PRE_RENDER)
	ge_GENERATE_TRAMPOLINE(postrender,	POST_RENDER)
>>>>>>> Stashed changes
	ge_END_CYCLE_HANDLER

private:
	static ge::GraphicsCore* gc;
<<<<<<< Updated upstream
	void viewSwitch();
=======

>>>>>>> Stashed changes
};
