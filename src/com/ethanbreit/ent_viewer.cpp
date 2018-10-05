#include <ent_viewer.h>


#include <inspector.h>
#include <util.h>
#include <string>
#include <custom_property_widgets.h>

#include <nuklear.h>
#include <ge/console/Log.h>
#include <ge/entity/EntityManager.h>
#include <ge/entity/Entity.h>
#include <ge/entity/component/Component.h>
#include <ge/entity/component/ComponentBatch.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>
#include <ge/entity/EntityTag.h>
#include <ge/engine/scene/SceneSerializer.h>
#include <ge/util/ResourceUtil.h>
#include <fileloader.h>
#include <ge/engine/scene/Scene.h>
#include <ge/loader/LoadScene.h>

int currently_selected_int = 0;
FileLoader* fileloader = nullptr;

void _draw_component(nk_context* ctx, ge::Component* comp, int id)
{
	nk_layout_row_dynamic(ctx, 20, 1);
	if (nk_tree_push_id(ctx, NK_TREE_TAB, comp->getTypeName().c_str(), NK_MINIMIZED, id))
	{
		if (nk_button_label(ctx, "Destroy"))
		{
			comp->getEntity()->removeComponent(comp->getTypeName());  //NOTE: concurrent modification?

			comp->getBatch()->hardRemove(comp->batchId);

			comp->destroy();

			free(comp);

			nk_tree_pop(ctx);
			//nk_end(ctx);
			return; //NOTE: continue not working...
		}
		int i = id*10;
		for (auto varName : comp->publicVarsDisplayOrder) //NOTE: this is bad
		{
			auto var = comp->publicVars[varName];

			draw_ep_auto(ctx, varName, var.first, var.second, i++);
		}
		nk_tree_pop(ctx);
	}
}

void _draw_component_popup(nk_context* ctx, ge::Entity* ent)
{
	//TEMP
	static bool addComponentMenuOpen = false;
	if (nk_button_label(ctx, "Add Component") || addComponentMenuOpen)
	{

		addComponentMenuOpen = true;
		if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Add Component POPUP", 0, nk_rect(10, 10, 200, 300)))
		{
			nk_layout_row_dynamic(ctx, 20, 1);
			if (nk_button_label(ctx, "cancel"))
			{
				addComponentMenuOpen = false;
				nk_popup_close(ctx);
				nk_popup_end(ctx);
				nk_end(ctx);
				return;
			}
			nk_layout_row_dynamic(ctx, 20, 1);
			nk_layout_row_dynamic(ctx, 20, 1);
			for (auto s : ge::ComponentConstructorRegistry::getAvailable())
			{
				if (ent->components.count(s))
					continue;
				if (nk_button_label(ctx, s.c_str()))
				{
					if (ent->components.count(s))
						break;

					ge::Component* cmp = ge::ComponentConstructorRegistry::newComponent(s, ent);

					cmp->insertToDefaultBatch();
					ent->insertComponent(cmp);
					addComponentMenuOpen = false;
					nk_popup_close(ctx);
				}
			}
			nk_popup_end(ctx);
		}
	}
}

void _inspector_entity_draw(nk_context* ctx, void* meta)
{
	int ent_i = *(int*)meta;
	ge::Entity* ent = ge::EntityManager::getAllEntities()->at(ent_i);
	if (ent == nullptr)
		return;

	nk_layout_row_dynamic(ctx, getRelativeHeight(0.01), 1);
	{
		char* editStr = (char*)malloc(ent->name.size() + 2);
		strcpy(editStr, ent->name.c_str());
		nk_edit_string_zero_terminated(ctx, NK_EDIT_SIMPLE, editStr, 64, 0);
		ent->name = std::string(editStr);
		free(editStr);
	}
	//nk_layout_row_dynamic(ctx, getRelativeHeight(0.90), 1);
	//if (nk_group_begin(ctx, "Component_List", NK_WINDOW_BORDER))
	nk_layout_row_dynamic(ctx, 25, 1);

	if (nk_button_label(ctx, "Destroy"))
	{
		ent->destroy();
		ge::EntityManager::removeEntity(ent);

		free(ent);

		ent = nullptr;

		return;
	}

	{
		int i = 0;
		for (auto c : ent->components)
			_draw_component(ctx, c.second, i++);



		nk_layout_row_dynamic(ctx, 30, 1);
		nk_layout_row_dynamic(ctx, 30, 1);

		_draw_component_popup(ctx, ent);

		//nk_group_end(ctx);
	}

}



void _draw_ent_list_element(nk_context* ctx, std::string name, int i)
{
	nk_color old_col = ctx->style.text.color;
	if(currently_selected_int==i)
		ctx->style.text.color = nk_rgb_hex("#E0D68A");

	struct nk_command_buffer *canvas;
	struct nk_input *input = &ctx->input;
	canvas = nk_window_get_canvas(ctx);

	struct nk_rect space;
	enum nk_widget_layout_states state;
	state = nk_widget(&space, ctx);
	if (!state) return;

	if (state != NK_WIDGET_ROM)
	{

		const struct nk_input *in = &ctx->input;
		if (nk_input_has_mouse_click_down_in_rect(in, NK_BUTTON_LEFT, space, 1))
		{
			currently_selected_int = i;
			set_inspection_content(_inspector_entity_draw, &currently_selected_int);
		}

	}

	if (currently_selected_int == i)
	{
		nk_fill_rect(canvas, space, 0, ctx->style.window.border_color);
		nk_draw_text(canvas, space, name.c_str(), name.length(), ctx->style.font, nk_rgb(255, 255, 255), ctx->style.window.header.label_active); //good enough for now...
	}
	else
	{
		nk_fill_rect(canvas, space, 0, ctx->style.window.background);
		nk_draw_text(canvas, space, name.c_str(), name.length(), ctx->style.font, nk_rgb(255, 0, 0), ctx->style.text.color);
	}

}

void _rend_thread_load_to_real(void* v_scene)
{
	ge::Empty::Scene* temp_scene = (ge::Empty::Scene*) v_scene;
	if (ge::Scene::currentScene == nullptr)
		ge::Scene::currentScene = new ge::Scene();
	
	ge::Scene::currentScene->loadScene(*temp_scene);
}

void _load_callback(std::string path)
{
	//clear
	std::list<ge::Entity*> remove_ents;
	for (auto e : *ge::EntityManager::getAllEntities())
	{
		if (e == nullptr)
			continue;

		for (auto t : e->tags)
			if (t->name == "no_export")
				goto _load_callback_end;
		//else (if it doesn't have the no_export tag)
		remove_ents.push_back(e);
		//if it does have the no_export tag skip
		_load_callback_end:
		continue;
	}
	for (auto e : remove_ents)
	{
		e->destroy();
		ge::EntityManager::removeEntity(e);
		free(e);
	}
	

	//load

	ge::Log::dbg("TEST"+path);
	ge::Empty::Scene* scene = new ge::Empty::Scene();
	ge::SceneLoader::loadSceneJson(path, scene, false);
	ge::RuntimeManager::getRuntime(RUNTIME_MAIN)->enqueFunction({_rend_thread_load_to_real, scene});
}

void _save_callback(std::string raw_url)
{
	ge::Log::dbg("TEST" + raw_url);
	std::string res_path = ge::ResourceUtil::getResPath("");
	std::string url = raw_url.substr(res_path.length(), raw_url.length() - res_path.length());

	ge::ResourceUtil::writeRawStrResource(url, ge::SceneSerializer::serializeCurrentSceneJson().dump(2));
}






void draw_ent_viewer(nk_context* ctx)
{
	if (nk_begin(ctx, "Entities", getRelativeRect_WIN(0, 0, 0.15f, 1), NK_WINDOW_TITLE | NK_WINDOW_BORDER))
	{
		nk_layout_row_dynamic(ctx, 20, 2);
		if (nk_button_label(ctx, "Load"))
		{
			fileloader = new FileLoader(ctx, true, false, _load_callback);
		}
		if (nk_button_label(ctx, "Save"))
		{
			fileloader = new FileLoader(ctx, true, true, _save_callback);
		}


		nk_layout_row_dynamic(ctx, 15, 1);
		if (nk_button_label(ctx, "New Entity"))
		{
			ge::Entity* nEnt = new ge::Entity();
			nEnt->name = "new_empty";
			ge::EntityManager::registerEntity(nEnt);
		}
		nk_layout_row_dynamic(ctx, 15, 1);

		for (auto ent : *ge::EntityManager::getAllEntities())
		{
			if (ent == nullptr)
				continue;
			nk_layout_row_dynamic(ctx, 20, 1);
			
			_draw_ent_list_element(ctx, ent->name, ent->id);
		}
		nk_end(ctx);
	}

	if (fileloader != nullptr)
		if (!fileloader->isFinished())
			fileloader->render();
}