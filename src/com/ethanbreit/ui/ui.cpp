#include <ui/ui.h>



#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "ui/file_loader/fileloader.h"
#include "ui/widgets/scene_widget.h"
#include "ui/widgets/staticobject_widget.h"


#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION


#include "nuklear.h"
#include "nuklear_glfw_gl3.h"
#include "input/MouseHandler.h"
#include "graphics/types/lights/LightDirectional.h"


using namespace ge;

GraphicsCore* ui::gc;

struct nk_context *ctx;
struct nk_colorf bg;

LightDirectional* ld;

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

void ui::init()
{
	GlobalRuntime::ge_REGISTER_RUNTIME_HANDLER;


	ui *u = new ui();
	GlobalMemory::insert("ui", { u, ReadableMemType::OTHER });


	gc = GlobalMemory::get("ge_renderer_instance").getRawData<GraphicsCore>();
	
	GlobalMemory::get("ge_update_runtime_group").getRawData<RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(u);
	GlobalMemory::get("ge_preuirender_runtime_group").getRawData<RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(u);
	GlobalMemory::get("ge_uirender_runtime_group").getRawData<RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(u);
	GlobalMemory::get("ge_postuirender_runtime_group").getRawData<RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(u);


	ld = GlobalMemory::get("testlight").getRawData<LightDirectional>();

	glfwSetInputMode(((GL::Window*)gc->window)->_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	MouseHandler::moveMouse = true;

	ctx = nk_glfw3_init(((GL::Window*)gc->window)->_window, NK_GLFW3_DEFAULT);
	struct nk_font_atlas *atlas;
	nk_glfw3_font_stash_begin(&atlas);
	
	nk_glfw3_font_stash_end();
	

}
ui::ui()
{
	GlobalRuntime::ge_REGISTER_RUNTIME_HANDLER;
	state = new int();
	value = new std::string();
}

void ui::preRender()
{
	nk_glfw3_new_frame();

}

void ui::render()
{



	

	if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
		NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
	{


		enum { EASY, HARD };
		static int op = EASY;
		static int property = 20;
		nk_layout_row_static(ctx, 30, 200, 1);
		if (nk_button_label(ctx, "File Explorer"))
			new FileLoader(ctx, state, value);
		nk_layout_row_static(ctx, 30, 200, 1);

		if (nk_button_label(ctx, "Scene"))
			new SceneWiget(ctx);

		nk_layout_row_static(ctx, 30, 200, 1);

		if (nk_button_label(ctx, "Static Objects"))
			new StaticObjectWidget(ctx);


		nk_layout_row_dynamic(ctx, 30, 2);
		if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
		if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, "Light Colour:", NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 25, 1);
		if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
			nk_layout_row_dynamic(ctx, 120, 1);
			bg = nk_color_picker(ctx, bg, NK_RGBA);
			nk_layout_row_dynamic(ctx, 25, 1);
			bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
			bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
			bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
			bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);

			ld->colour.x = bg.r;
			ld->colour.y = bg.g;
			ld->colour.z = bg.b;

			nk_combo_end(ctx);
		}

		nk_end(ctx);
	}

	
}

void ui::postRender()
{
	nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);


}

void ui::update()
{
}
