#include <core/core.h>
#include "graphics/meshes/debug/DebugVertexTriangleMesh.h"
#include "memory/GlobalMemory.h"
#include "ui/ui.h"
#include "input/KeyboardHandler.h"
#include "input/MouseHandler.h"


using namespace ge;


GraphicsCore* Core::gc;




Core::Core()
{
	GlobalRuntime::ge_REGISTER_RUNTIME_HANDLER;
	gc = GlobalMemory::get("ge_renderer_instance").getRawData<GraphicsCore>();
}

void Core::update()
{
	viewSwitch();
}

void Core::prerender()
{
	//INIT
	static bool initialised = false;
	if(!initialised)
	{
		initialised = true;
		gc->window->makeCurrentThread(GlobalMemory::get("ge_render_context_runtime").getRawData<Runtime>());
		gc->window->setClearColour({ 0.2f, 0.3f, 0.3f }); /// self explanatory (has to be here becuase OpenGL is bad with multithreading)



		//INIT THINGS
		ui::init();
	}

	gc->window->clear();
	glEnable(GL_DEPTH_TEST);
}

void Core::finalRender()
{
	gc->window->swap();
}





void Core::viewSwitch()
{
	static bool first = true;
	if (KeyboardHandler::keyDownSticky(KeyboardKey::V))
	{
		if (first) {
			//Enable View
			if (MouseHandler::moveMouse)
			{
				ConsoleIO::print("View Mode\n");

				MouseHandler::moveMouse = false;
				MouseHandler::centerMouse = true;
				//glfwSetInputMode(((GL::Window*)gc->window)->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			}
			else
			{
				ConsoleIO::print("Edit Mode\n");

				MouseHandler::moveMouse = true;
				MouseHandler::centerMouse = false;

				//glfwSetInputMode(((GL::Window*)gc->window)->_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
		first = false;
	}
	else
	{
		first = true;
	}
}