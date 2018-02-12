#include <graphics/GraphicsCore.h>
#include "ge/graphics/enums/GraphicsApi.h"
#include "graphics/types/Window.h"
#include "error/Error.h"
#include "memory/GlobalMemory.h"

#include <core/core.h>
#include "graphics/Camera.h"
#include "debug/FreeMove.h"
#include "graphics/types/lights/LightDirectional.h"
#include "test.h"

using namespace ge;

int main()
{
	GraphicsCore* gc = new ge::GraphicsCore(GraphicsApi::OpenGL);
	
	Core* core = new Core();

	//Window Creation
	WindowConstructorInfo wci = WindowConstructorInfo();

	wci.height = 1080;
	wci.width = 1920;
	wci.glMajorVersion = 4;
	wci.glMinorVersion = 4;
	wci.hiddenCursor = false;

	gc->window->init(wci);
	gc->window->setClearColour({ 0.2f, 0.3f, 0.3f });


	//Runtime Creation
	Runtime *update = new Runtime("update", 60);
	Runtime *render = new Runtime("render", 60);
	Runtime *load = new Runtime("load", 1);

	GlobalMemory::insert("ge_render_context_runtime", GlobalMemory::MemItem(render, ReadableMemType::OTHER));



	RuntimeGroup *updateGroup		= new RuntimeGroup();

	RuntimeGroup *preRenderGroup	= new RuntimeGroup();
	RuntimeGroup *renderGroup		= new RuntimeGroup();
	RuntimeGroup *postRenderGroup	= new RuntimeGroup();


	RuntimeGroup *preUIRenderGroup = new RuntimeGroup();
	RuntimeGroup *UIrenderGroup = new RuntimeGroup();
	RuntimeGroup *postUIRenderGroup = new RuntimeGroup();


	RuntimeGroup *finalRenderGroup = new RuntimeGroup();


	RuntimeGroup *loadGroup			= new RuntimeGroup();

	update->insertGroup(updateGroup);

	render->insertGroup(preRenderGroup,	0);
	render->insertGroup(renderGroup,	1);
	render->insertGroup(postRenderGroup,2);


	render->insertGroup(preUIRenderGroup, 3);
	render->insertGroup(UIrenderGroup, 4);
	render->insertGroup(postUIRenderGroup, 5);

	render->insertGroup(finalRenderGroup, 6);


	load->insertGroup(loadGroup);

	updateGroup->runtimeId		= UPDATE;
	GlobalMemory::insert("ge_update_runtime_group", { updateGroup,ReadableMemType::OTHER });

	preRenderGroup->runtimeId	= PRE_RENDER;
	renderGroup->runtimeId		= RENDER;
	postRenderGroup->runtimeId	= POST_RENDER;

	preUIRenderGroup->runtimeId = 8;
	UIrenderGroup->runtimeId = 9;
	postUIRenderGroup->runtimeId = 10;


	finalRenderGroup->runtimeId =  12; //Add proper definition

	GlobalMemory::insert("ge_prerender_runtime_group", { preRenderGroup,ReadableMemType::OTHER });
	GlobalMemory::insert("ge_render_runtime_group", { renderGroup,ReadableMemType::OTHER });
	GlobalMemory::insert("ge_postrender_runtime_group", { postRenderGroup,ReadableMemType::OTHER });
	GlobalMemory::insert("ge_finalrender_runtime_group", { postRenderGroup,ReadableMemType::OTHER });

	GlobalMemory::insert("ge_preuirender_runtime_group", { preUIRenderGroup,ReadableMemType::OTHER });
	GlobalMemory::insert("ge_uirender_runtime_group", { UIrenderGroup,ReadableMemType::OTHER });
	GlobalMemory::insert("ge_postuirender_runtime_group", { postUIRenderGroup,ReadableMemType::OTHER });

	loadGroup->runtimeId		= LOADER;
	GlobalMemory::insert("ge_load_context_runtime", { load,ReadableMemType::OTHER });

	//Core to Runtime Linking

	preRenderGroup	->ge_RUNTIME_GROUP_INSERT_HEAP(core);
	finalRenderGroup	->ge_RUNTIME_GROUP_INSERT_HEAP(core);
	updateGroup		->ge_RUNTIME_GROUP_INSERT_HEAP(core);






	//DEMO DEMO DEMO

	ge::Camera *camera = new ge::Camera();
	camera->nearCull = 0.1f;
	camera->farCull = 100.0f;
	camera->aspectRatio = ((float)wci.width) / ((float)wci.height);
	//camera.fov = 90.0f/100.0f; ///Divide by 100 to convert fov to radians.
	camera->fov = glm::radians(45.0f);
	camera->up = glm::vec3(0, 1, 0);
	camera->pos = glm::vec3(0, 0, 0);
	camera->dir = glm::vec3(0, 0, -1);



	GlobalMemory::insert(DBL_STRINGIFY(CURRENT_CAMERA), { camera,ReadableMemType::OTHER });

	ge::FreeMove* fm = new ge::FreeMove();
	fm->speed = 0.05f;
	fm->lookSpeed = 0.0007f;
	fm->_position = glm::vec3(0);

	///initialising data
	fm->_horizontalAngle = 0;
	fm->_verticalAngle = 0;




	LightDirectional* dirLight = new LightDirectional();
	dirLight->dir = glm::vec3(1, -0.5, 0);
	dirLight->colour = glm::vec3(1, 1, 1);


	GlobalMemory::insert("testlight", { dirLight,ReadableMemType::OTHER });

	new test(fm,camera);


	postRenderGroup	->ge_RUNTIME_GROUP_INSERT_HEAP(core);
	updateGroup		->ge_RUNTIME_GROUP_INSERT_HEAP(core);

	while (true)
	{
		gc->window->poll();
	}

}