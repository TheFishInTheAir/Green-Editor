#include <ent_viewer.h>
#include <game_viewer.h>
#include <resource_interface.h>
#include <bullshit.h>
#include <inspector.h>


#include <GL/glew.h>
#include <nuklear.h>
#include <nuklear_glfw_gl3.h>
//NOTE: I SPENT OVER A FUCKING WEEK TRYING TO GET THE GAME VIEWER WORKING AND IT WAS ACTUALLY JUST GLFW GL4 FUCKING UP!
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024



#include <ge/engine/Start.h>
#include <ge/graphics/GraphicsCore.h>
#include <ge/util/PreprocessorUtil.h>
#include <ge/console/Log.h>
#include <engine/global_settings.pre>
//#include <ge/debug/DebugGUI.h>

nk_context* nctx;




void setupStyle()
{
	__this_is_bullshit_i_need_to_get_this_shit_to_work(); //NOTE: BULLSHIT
	nctx->style.window.background = nk_rgb_hex("#170513");
	nctx->style.window.fixed_background = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.window.border = 2;
	nctx->style.window.border_color = nk_rgb_hex("#8E443D");

	nctx->style.window.header.active = nk_style_item_color(nk_rgb_hex("#8E443D"));
	nctx->style.window.header.normal = nk_style_item_color(nk_rgb_hex("#68322D"));
	nctx->style.window.header.label_active = nk_rgb_hex("#170513");
	nctx->style.text.color = nk_rgb_hex("#CB9173");

	nctx->style.edit.normal = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.edit.hover  = nk_style_item_color(nk_rgb_hex("#270513"));
	nctx->style.edit.active = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.edit.border_color = nk_rgb_hex("#CB9173");
	nctx->style.edit.text_normal = nk_rgb_hex("#8E443D");
	nctx->style.edit.text_hover = nk_rgb_hex("#8E443D");
	nctx->style.edit.text_active = nk_rgb_hex("#8E443D");
	nctx->style.edit.cursor_text_normal = nk_rgb_hex("#CB9173");
	nctx->style.edit.cursor_size = 0.01f;
	nctx->style.edit.cursor_normal = nk_rgb_hex("#CB9173");
	nctx->style.edit.cursor_hover  = nk_rgb_hex("#CB9173");
	nctx->style.edit.cursor_text_hover = nk_rgba_hex("#170513");

	nctx->style.tab.background   = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.tab.border = 1;
	nctx->style.tab.border_color = nk_rgb_hex("#68322D");
	nctx->style.tab.tab_maximize_button.normal = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.tab.tab_maximize_button.text_normal = nk_rgb_hex("#68322D");
	nctx->style.tab.tab_minimize_button.normal = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.tab.tab_minimize_button.text_normal = nk_rgb_hex("#68322D");
	nctx->style.tab.text		 = nk_rgb_hex("#CB9173");
	nctx->style.tab.node_maximize_button.normal = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.tab.node_minimize_button.normal = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.tab.node_maximize_button.text_normal = nk_rgb_hex("#CB9173");
	nctx->style.tab.node_minimize_button.text_normal = nk_rgb_hex("#CB9173");
	//Property
	nctx->style.property.normal = nk_style_item_color(nk_rgb_hex("#68322D"));
	nctx->style.property.hover  = nk_style_item_color(nk_rgb_hex("#68322D"));
	nctx->style.property.active = nk_style_item_color(nk_rgb_hex("#CB9173"));
	nctx->style.property.label_normal = nk_rgb_hex("#170513");
	nctx->style.property.label_active = nk_rgb_hex("#170513");
	nctx->style.property.label_hover  = nk_rgb_hex("#170513");
	nctx->style.property.edit.text_normal = nk_rgb_hex("#170513");
	nctx->style.property.edit.text_hover  = nk_rgb_hex("#170513");
	nctx->style.property.edit.text_active = nk_rgb_hex("#170513");
	nctx->style.property.edit.normal = nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.edit.active = nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.edit.hover  = nk_style_item_color(nk_rgba(0, 0, 0, 0));

	nctx->style.property.edit.cursor_normal			= nk_rgb_hex("#170513");
	nctx->style.property.edit.cursor_hover			= nk_rgb_hex("#170513");
	nctx->style.property.edit.selected_normal		= nk_rgb_hex("#170513");
	nctx->style.property.edit.selected_hover		= nk_rgb_hex("#170513");
	nctx->style.property.edit.cursor_text_normal	= nk_rgb_hex("#68322D");
	nctx->style.property.edit.cursor_text_hover		= nk_rgb_hex("#68322D");
	nctx->style.property.edit.selected_text_normal	= nk_rgb_hex("#68322D");
	nctx->style.property.edit.selected_text_hover	= nk_rgb_hex("#68322D");
	nctx->style.property.inc_button.normal			= nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.inc_button.active			= nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.inc_button.hover			= nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.inc_button.text_normal		= nk_rgb_hex("#170513");
	nctx->style.property.inc_button.text_hover		= nk_rgb_hex("#8E443D");
	nctx->style.property.inc_button.text_active		= nk_rgb_hex("#CB9173");
	nctx->style.property.dec_button.normal			= nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.dec_button.active			= nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.dec_button.hover			= nk_style_item_color(nk_rgba(0, 0, 0, 0));
	nctx->style.property.dec_button.text_normal		= nk_rgb_hex("#170513");
	nctx->style.property.dec_button.text_hover		= nk_rgb_hex("#8E443D");
	nctx->style.property.dec_button.text_active		= nk_rgb_hex("#CB9173");


	//Button
	nctx->style.button.normal = nk_style_item_color(nk_rgb_hex("#170513"));
	nctx->style.button.hover  = nk_style_item_color(nk_rgb_hex("#270513"));
	nctx->style.button.active = nk_style_item_color(nk_rgb_hex("#CB9173"));
	nctx->style.button.border = 1;
	nctx->style.button.border_color = nk_rgb_hex("#68322D");
	nctx->style.button.text_normal = nk_rgb_hex("#CB9173");
	nctx->style.button.text_hover  = nk_rgb_hex("#CB9173");
	nctx->style.button.text_active = nk_rgb_hex("#170513");
	

}



void drawUI()
{
	if (ge::GraphicsCore::ctx->currentPipeline->getState() != ge::PipelineState::PostRender)
		return;

	nk_glfw3_new_frame();

	draw_ent_viewer(nctx);
	draw_inspector(nctx);
	draw_game_viewer(nctx);
	draw_resource_interface(nctx);

	draw_test_game_viewer();
	nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
	glEnable(GL_DEPTH_TEST);
	

}

struct ui_hook
{
	//static ui_hook* ctx;
	ui_hook()
	{
		ge_REGISTER_RUNTIME_HANDLER

		ge::RuntimeManager::getRuntime(RUNTIME_MAIN)->getGroup(PIPELINE_ROUTER_RG)->
			ge_RUNTIME_GROUP_INSERT_HEAP(this);
	}
	void init()
	{
		nctx = nk_glfw3_init(((ge::GL::Window*)ge::GraphicsCore::ctx->window)->_window, NK_GLFW3_INSTALL_CALLBACKS); //last two are arbitrary defaults
		
		{struct nk_font_atlas *atlas;
		nk_glfw3_font_stash_begin(&atlas);
		nk_glfw3_font_stash_end();}

		setupStyle();

		//ctx = this;
	}

	void cycle()
	{
		static bool shouldInit = true;
		if (shouldInit)
		{
			shouldInit = false;
			ge::GraphicsCore::ctx->window->makeCurrentThread(ge::RuntimeManager::getRuntime(RUNTIME_MAIN));
			init();
		}
		drawUI();
	}

	ge_START_CYCLE_HANDLER(ui_hook)
		ge_GENERATE_TRAMPOLINE(cycle, PIPELINE_ROUTER_RG)
	ge_END_CYCLE_HANDLER
};

int main()
{
	ge::RuntimeGroup* update = new ge::RuntimeGroup();
	update->runtimeId = UPDATE;

	ge::SimpleEngineCreationInfo seci;
	seci.g_api = ge::GraphicsApi::OpenGL;
	seci.wci.height = 1080;
	seci.wci.width = 1920;
	seci.wci.gl_major_version = 3;
	seci.wci.gl_minor_version = 3;
	seci.wci.clear_colour = glm::vec3(79.0f / 255, 100.0f / 255, 20 / 255);
	seci.wci.hidden_cursor = false;
	seci.wci.samples = 0;
	seci.runtimes.push_back(new ge::Runtime(RUNTIME_MAIN));
	seci.runtime_groups.push_back({ update, RUNTIME_MAIN });

	ge::simpleStart(seci);

	new ui_hook();

	ge::GraphicsCore::ctx->window->mainThreadPollLoop();
	std::exit(0);
}

/*int main()
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

}*/