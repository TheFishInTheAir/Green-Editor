#pragma once
#include "runtime/Runtime.h"
#include <engine/global_settings.pre>
#include "debug/FreeMove.h"

struct test
{
	test(ge::FreeMove*, ge::Camera*);
	void update();

	ge_START_CYCLE_HANDLER(test)
		ge_GENERATE_TRAMPOLINE(update, UPDATE)
		ge_END_CYCLE_HANDLER

	ge::FreeMove* fm;
	ge::Camera* camera;
};
