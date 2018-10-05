#include <inspector.h>
#include <util.h>
#include <string>
#include <nuklear.h>
#include <ge/console/Log.h>
#include <ge/entity/EntityManager.h>
#include <ge/entity/Entity.h>
#include <ge/entity/component/Component.h>
#include <ge/entity/component/ComponentBatch.h>
#include <fileloader.h>
#include <ge/engine/scene/Scene.h>
#include <ge/loader/LoadScene.h>

typedef struct //TODO: add option to delete on change
{
	void* current_meta;
	void(*current_content_function)(nk_context*, void*);
	bool should_free = false;
} inspection_context;

inspection_context* ic = nullptr;

void set_inspection_content(void(*function)(nk_context*, void*), void* meta, bool should_free)
{
	if (ic == nullptr)
		ic = new inspection_context();

	if (ic->should_free)
	{
		free(ic->current_meta);
		ic->should_free = false;
	}

	ic->current_meta = meta;
	ic->current_content_function = function;
	ic->should_free = should_free;
}

void set_inspection_content(void(*function)(nk_context*, void*), void* meta)
{
	if (ic == nullptr)
		ic = new inspection_context();

	if (ic->should_free)
	{
		free(ic->current_meta);
		ic->should_free = false;
	}

	ic->current_meta = meta;
	ic->current_content_function = function;
}

void* get_current_inspection_meta()
{
	if (ic == nullptr)
		return nullptr;
	return ic->current_meta;
}

void draw_inspector(nk_context* ctx)
{
	if (ic == nullptr)
		ic = new inspection_context();
	

	if (nk_begin(ctx, "Inspector", getRelativeRect_WIN(1.0f - 0.15f, 0, 0.15f, 1), NK_WINDOW_TITLE | NK_WINDOW_BORDER))
	{
		if(ic->current_content_function!=nullptr)
			ic->current_content_function(ctx, ic->current_meta);
		else
		{
			nk_layout_row_dynamic(ctx, 70, 1);
			nk_label(ctx, "Nothing Selected", NK_TEXT_ALIGN_CENTERED);
		}
		nk_end(ctx);
	}
}



