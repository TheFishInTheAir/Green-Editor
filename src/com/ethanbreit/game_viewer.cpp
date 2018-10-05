#include <game_viewer.h>
#include <bullshit.h>
#include <util.h>
#include <string>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include <nuklear.h>
#include <ge/console/Log.h>
#include <ge/graphics/GraphicsCore.h>
#include <ge/entity/EntityManager.h>
#include <ge/entity/Entity.h>
#include <ge/entity/component/Component.h>
#include <ge/entity/component/ComponentBatch.h>
#include <ge/graphics/abs/OpenGL/types/GLTexture.h>
#include <fileloader.h>
#include <ge/input/KeyboardHandler.h>
#include <ge/input/MouseHandler.h>
#include <ge/graphics/abs/OpenGL/meshes/GLTriangleMesh.h>
#include <ge/default_geom/Cube.h>
#include <ge/loader/LoadShader.h>


struct game_viewer_context
{
	ge::GL::TriangleMesh* mesh = nullptr;
	ge::GL::ShaderGroup*  program = nullptr;
	ge::FrameBuffer* fbo = nullptr;
	ge::GL::Texture*	 fbo_color_attachment = nullptr;
	bool mouseState = false;
};

game_viewer_context* gvc = nullptr;

const float _gv_w_off = 0.7f;
const float _gv_h_off = _gv_w_off; //preserve aspect ratio...

void init_game_viewer_context()
{
	if (gvc == nullptr)
		gvc = new game_viewer_context();
	
	if (gvc->mesh != nullptr || gvc->program != nullptr)
		return;

	//Context Initialisation
	
	gvc->mesh = (ge::GL::TriangleMesh*) ge::GraphicsCore::ctx->meshFactory->newTriangleMesh(ge::dgeo::cube::getMeshData());
	ge::ShaderLoader::loadShader("engine/defaults/forward/unlit/vo_textured.gesm", (ge::ShaderGroup**)&(gvc->program));
	gvc->mesh->setShaderGroup((ge::ShaderGroup*)gvc->program);
	gvc->mesh->rebuffer();
}

void draw_test_game_viewer()
{
	init_game_viewer_context(); //mildly inneficient but remember 80 20

	gvc->mesh->render();
}

void test_fb_init()
{

	ge::GraphicsCore::ctx->textureFactory->genFramebuffer(1920, 1080, &(gvc->fbo)); //test resolutions
	gvc->fbo->bind();

	gvc->fbo->generateTextureAttachment(ge::FrameBufferAttachment::Colour);
	ge::Log::err(std::to_string(gvc->fbo->hasDepth()) + ": FUCK 1");
	//gvc->fbo->generateBufferAttachment(ge::FrameBufferAttachment::Depth24_Stencil8);
	gvc->fbo->generateTextureAttachment(ge::FrameBufferAttachment::Depth); //the texture doesn't seem to works
	ge::Log::err(std::to_string(gvc->fbo->hasDepth())+": FUCK 2");

	gvc->fbo_color_attachment = (ge::GL::Texture*) gvc->fbo->getTextureAttachment(ge::FrameBufferAttachment::Colour);
	gvc->fbo_color_attachment->setFiltering(ge::TextureFilterType::Bilinear);
	gvc->mesh->registerTexture(gvc->fbo_color_attachment, ALBEDO_LOC);
	gvc->mesh->setUniform(DBL_STRINGIFY(ALBEDO_REF), ALBEDO_LOC);
	glm::mat4 scaled_mvp = glm::scale( glm::translate(glm::mat4(), { 0, 0.1f, 0 }),  { _gv_w_off*2, _gv_h_off*2, 1 } );
	//scaled_mvp = glm::translate(scaled_mvp, {0, 0.1f, 0});
	gvc->mesh->setUniform(DBL_STRINGIFY(MVP), scaled_mvp);

	//glEnable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);

	gvc->fbo->bindDefault();

}

void update_pipeline()
{
	init_game_viewer_context(); //mildly inneficient but remember 80 20

	if (gvc->fbo == nullptr)
		test_fb_init();

	if (ge::GraphicsCore::ctx->currentPipeline == nullptr)
		return;

	for (auto stage : ge::GraphicsCore::ctx->currentPipeline->stages)
	{
		if (stage->framebuffer == nullptr && !stage->overrideSG)
			stage->framebuffer = gvc->fbo;
	}
}

void toggleMouse()
{
	static bool justPresesd = false;
	if (ge::KeyboardHandler::keyDownSticky(ge::KeyboardKey::P))
	{
		if (!justPresesd)
		{
			if (gvc->mouseState)
			{ //CLOSE
				ge::MouseHandler::queueMouseDisableStateChange(true);
				//glfwSetInputMode(((ge::GL::Window*) GraphicsCore::ctx->window)->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				ge::MouseHandler::disabled = false;
			}
			else
			{ //OPEN NOTE: only works on osx
				ge::MouseHandler::queueMouseDisableStateChange(false);
				ge::MouseHandler::disabled = true;

			}
			gvc->mouseState = !gvc->mouseState;
		}
		justPresesd = true;
	}
	else
	{
		justPresesd = false;
	}
}

void draw_game_viewer(nk_context* ctx)
{
	if(gvc!=nullptr)
		if (gvc->fbo != nullptr)
		{
			auto old_fixed_background = ctx->style.window.fixed_background;
			auto old_background = ctx->style.window.background;

			ctx->style.window.fixed_background = nk_style_item_color(nk_rgba(0,0,0,0));
			ctx->style.window.background = nk_rgba(0, 0, 0, 0);

			if (nk_begin(ctx, "GameViewer", getRelativeRect_WIN(0.15f, 0.1f, 0.7f, 0.7f), 0))
			{
				toggleMouse();


				ge::Runtime* r = ge::RuntimeManager::getRuntime(RUNTIME_MAIN);
				nk_layout_row_dynamic(ctx, 10, 1);
				nk_label(ctx, (std::string("Target FPS: ") + (r->cyclesPerSecond == 0 ? "Unlocked" : "t" + std::to_string(r->cyclesPerSecond))).c_str(), NK_TEXT_RIGHT);
				nk_label(ctx, (std::string("Last FPS: ") + std::to_string(r->getLastManagesCycles())).c_str(), NK_TEXT_RIGHT);

				nk_end(ctx);
			}

			ctx->style.window.fixed_background = old_fixed_background;
			ctx->style.window.background = old_background;
			return;
		}

	if (nk_begin(ctx, "GameViewer", getRelativeRect_WIN(0.15f, 0.5f-0.05f-(0.7f/2), 0.7f, 0.7f), 0))
	{
		nk_layout_row_dynamic(ctx, 60, 1);
		if (nk_button_label(ctx, "Force Pipeline FBO Override"))
			update_pipeline();

		nk_layout_row_dynamic(ctx, 420, 1);
		nk_label(ctx, "Pipeline Default FBO not overriden", NK_TEXT_CENTERED);

        //_draw_frame_buffer(ctx);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // int texId = (int)((ge::GL::Texture*)(ge::Scene::currentScene->shadows.front()->shadowMap))->id;                                           //
		// glBindTexture(GL_TEXTURE_2D, texId);                                                                                                      //
		// auto img = nk_image_id(texId);                                                                                                            //
		// struct nk_vec2 upperCord = nk_window_get_content_region_min(ctx);                                                                         //
        //                                                                                                                                           //
		// //nk_stroke_line(nk_window_get_canvas(ctx), upperCord.x, upperCord.y, upperCord.x+30, upperCord.y+30, 1.0f, nk_rgba(255,255,100,255));    //
		// nk_draw_image(nk_window_get_canvas(ctx), nk_rect(upperCord.x, upperCord.y, y*0.30f, y*0.30f), &img, nk_rgba(255, 255, 255, 255));         //
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		nk_end(ctx);
	}
}