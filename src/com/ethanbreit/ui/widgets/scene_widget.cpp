#include <ui/widgets/scene_widget.h>
#include "ui/file_loader/fileloader.h"
#include "loader/LoadScene.h"
#include "memory/GlobalMemory.h"


SceneWiget::SceneWiget(nk_context* ctx)
{
	ge::GlobalRuntime::ge_REGISTER_RUNTIME_HANDLER;
	scenePathState = -1;
	scene = new ge::Scene();
	scene->init();
	this->ctx = ctx;

	ge::GlobalMemory::insert("ge_current_scene", { scene, ge::ReadableMemType::OTHER }); //TODO: IMPROVE THIS IS DEMO CODE


	ge::GlobalMemory::get("ge_update_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);
	ge::GlobalMemory::get("ge_uirender_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);

}

void SceneWiget::render()
{
	if(shouldLoad)
	{
		shouldLoad = false;
		scene->loadScene(sceneTemplate);
	}

	if (nk_begin(ctx, "Scene", nk_rect(350, 50, 430, 450),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE |
		NK_WINDOW_CLOSABLE | NK_WINDOW_TITLE))
	{
		
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, std::string("Current Scene Directory: "+scenePath).c_str(), NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 20, 1);
		if (nk_button_label(ctx, "File Explorer"))
			(new FileLoader(ctx, &scenePathState, &scenePath))->setResource();
		nk_end(ctx);
	}



}

void SceneWiget::update()
{
	if(scenePathState==1)
	{
		//Should be in loading thread
		ge::SceneLoader::loadSceneJson(scenePath, &sceneTemplate, false);
		shouldLoad = true;
		scenePathState = -1;
	}
}
