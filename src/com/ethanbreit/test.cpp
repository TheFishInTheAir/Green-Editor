#include <test.h>
#include "memory/GlobalMemory.h"
#include "input/MouseHandler.h"

test::test(ge::FreeMove* fm, ge::Camera* camera)
{
	ge::GlobalRuntime::ge_REGISTER_RUNTIME_HANDLER;


	this->fm = fm;
	this->camera = camera;

	ge::GlobalMemory::get("ge_update_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);

}

void test::update()
{
	if (ge::MouseHandler::centerMouse)
	{
		fm->update(camera);
		camera->update();
	}
}
