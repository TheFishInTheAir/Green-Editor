#include <custom_property_widgets.h>

#include <inspector.h>
#include <util.h>

#include <ge/engine/enum/DataTypes.h>

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



void draw_ep_auto(nk_context* ctx, std::string name, ge::DataType::type t, void* v, int id)
{
	switch (t)
	{
	case ge::DataType::BOOL:
		draw_ep_bool(ctx, name, (bool*)v);
		break;
	case ge::DataType::FLOAT:
		draw_ep_float(ctx, name, (float*)v);
		break;
	case ge::DataType::INT:
		draw_ep_int(ctx, name, (int*)v);
		break;
	case ge::DataType::FVEC3:
		draw_ep_vec3(ctx, name, (glm::vec3*)v, id);
		break;
	case ge::DataType::QUAT:
		draw_ep_quaternion(ctx, name, (glm::quat*)v, id);
		break;
	case ge::DataType::COLOUR3:
		draw_ep_col3(ctx, name, (glm::vec3*)v, id);
		break;
	case ge::DataType::MATERIAL:
		draw_ep_material(ctx, name, (std::string*) v);
		break;
	case ge::DataType::TEXTURE:
		draw_ep_texture(ctx, name, (std::string*) v);
		break;
	case ge::DataType::MESH_DATA:
		draw_ep_mesh_data(ctx, name, (std::string*) v);
		break;
	case ge::DataType::AUDIO_CLIP:
		draw_ep_audio_clip(ctx, name, (std::string*) v);
		break;
	case ge::DataType::SHADER_GROUP:
		draw_ep_shader_group(ctx, name, (std::string*) v);
		break;

	}
}


void draw_ep_float(nk_context* nctx, std::string name, float* v)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.66666f);

	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.33333f);

	nk_property_float(nctx, "#", -1000000, v, 1000000, 0.10f, 0.1f);

	nk_layout_row_end(nctx);
}



void draw_ep_bool(nk_context* nctx, std::string name, bool *v)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.66666f);

	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.33333f);

	if (nk_button_label(nctx, (*v ? "True" : "False")))
		*v = !*v;

	nk_layout_row_end(nctx);
}

void draw_ep_int(nk_context* nctx, std::string name, int *v)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.66666f);

	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.33333f);

	nk_property_int(nctx, "#", -1000, v, 1000, 1, 0.1f);


	nk_layout_row_end(nctx);
}

void draw_ep_material(nk_context* nctx, std::string name, std::string* text)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.66666f);


	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.33333f);

	static std::string* currentSelected = nullptr;
	if (nk_button_label(nctx, text->c_str()))
		currentSelected = text;

	if (currentSelected != nullptr)
		if (nk_popup_begin(nctx, NK_POPUP_STATIC, "DebugGUI: Material Selector", 0, nk_rect(10, 10, 200, 300)))
		{
			nk_layout_row_dynamic(nctx, 20, 1);
			for (auto s : ge::Scene::currentScene->materials)
			{
				if (nk_button_label(nctx, s.second.name.c_str()))
				{
					*currentSelected = s.second.name;
					currentSelected = nullptr;
					nk_popup_close(nctx);
				}
			}
			nk_popup_end(nctx);
		}


	nk_layout_row_end(nctx);
}


void draw_ep_texture(nk_context* nctx, std::string name, std::string* text)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.33333f);


	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.66666f);

	static std::string* currentSelected = nullptr;
	if (nk_button_label(nctx, text->c_str()))
		currentSelected = text;

	if (currentSelected != nullptr)
		if (nk_popup_begin(nctx, NK_POPUP_STATIC, "DebugGUI: Texture Selector", 0, nk_rect(10, 10, 200, 300)))
		{
			nk_layout_row_dynamic(nctx, 20, 1);
			for (auto s : ge::Scene::currentScene->textures)
			{
				if (nk_button_label(nctx, s.first.c_str()))
				{
					*currentSelected = s.first;
					currentSelected = nullptr;
					nk_popup_close(nctx);
				}
			}
			nk_popup_end(nctx);
		}


	nk_layout_row_end(nctx);
}


void draw_ep_mesh_data(nk_context* nctx, std::string name, std::string* text)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.66666f);


	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.33333f);

	static std::string* currentSelected = nullptr;
	if (nk_button_label(nctx, text->c_str()))
		currentSelected = text;

	if (currentSelected != nullptr)
		if (nk_popup_begin(nctx, NK_POPUP_STATIC, "DebugGUI: Mesh Data Selector", 0, nk_rect(10, 10, 200, 300)))
		{
			nk_layout_row_dynamic(nctx, 15, 1);
			for (auto s : ge::Scene::currentScene->meshes)
			{
				if (nk_button_label(nctx, s.first.c_str()))
				{
					*currentSelected = s.first;
					currentSelected = nullptr;
					nk_popup_close(nctx);
				}
			}
			nk_popup_end(nctx);
		}


	nk_layout_row_end(nctx);
}

void draw_ep_audio_clip(nk_context* nctx, std::string name, std::string* text)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.66666f);


	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.33333f);

	static std::string* currentSelected = nullptr;
	if (nk_button_label(nctx, text->c_str()))
		currentSelected = text;

	if (currentSelected != nullptr)
		if (nk_popup_begin(nctx, NK_POPUP_STATIC, "DebugGUI: Audio Clip Selector", 0, nk_rect(10, 10, 200, 300)))
		{
			nk_layout_row_dynamic(nctx, 15, 1);
			for (auto s : ge::Scene::currentScene->audioClips)
			{
				if (nk_button_label(nctx, s.first.c_str()))
				{
					*currentSelected = s.first;
					currentSelected = nullptr;
					nk_popup_close(nctx);
				}
			}
			nk_popup_end(nctx);
		}


	nk_layout_row_end(nctx);
}

void draw_ep_shader_group(nk_context* nctx, std::string name, std::string* text)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.33333);


	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.66666f);

	static std::string* currentSelected = nullptr;
	if (nk_button_label(nctx, text->c_str()))
		currentSelected = text;

	if (currentSelected != nullptr)
		if (nk_popup_begin(nctx, NK_POPUP_STATIC, "DebugGUI: Shader Group Selector", 0, nk_rect(-200, 10, 400, 300)))
		{
			nk_layout_row_dynamic(nctx, 15, 1);
			for (auto s : ge::Scene::currentScene->shaderGroups)
			{
				if (nk_button_label(nctx, s.first.c_str()))
				{
					*currentSelected = s.first;
					currentSelected = nullptr;
					nk_popup_close(nctx);
				}
			}
			nk_popup_end(nctx);
		}


	nk_layout_row_end(nctx);
}

void draw_ep_quaternion(nk_context* ctx, std::string name, glm::quat *v, int id)
{

	auto old_text = ctx->style.tab.text;
	ctx->style.tab.text = ctx->style.text.color;

	if (nk_tree_push_id(ctx, NK_TREE_NODE, name.c_str(), NK_MINIMIZED, id))
	{
		nk_layout_row_dynamic(ctx, 20, 1);

		glm::vec3 euler = glm::degrees(glm::eulerAngles(*v));
		float f = glm::radians(0.0f);

		nk_property_float(ctx, "#", -1000000, &(euler.x), 1000000, 0.50f, 0.5f);
		nk_property_float(ctx, "#", -1000000, &(euler.y), 1000000, 0.50f, 0.5f);
		nk_property_float(ctx, "#", -1000000, &(euler.z), 1000000, 0.50f, 0.5f);


		*v = glm::quat(glm::radians(euler));

		nk_tree_pop(ctx);
	}
	ctx->style.tab.text = old_text;
	/*

	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.2);

	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.8);
	glm::vec3 euler = glm::degrees(glm::eulerAngles(*v));
	float f = glm::radians(0.0f);


	if (nk_group_begin(nctx, "float_input_group", NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(nctx, 20, 3);
		nk_property_float(nctx, "#", -1000000, &(euler.x), 1000000, 0.50f, 0.5f);
		nk_property_float(nctx, "#", -1000000, &(euler.y), 1000000, 0.50f, 0.5f);
		nk_property_float(nctx, "#", -1000000, &(euler.z), 1000000, 0.50f, 0.5f);

		nk_group_end(nctx);
	}

	*v = glm::quat(glm::radians(euler));
	nk_layout_row_end(nctx);
	*/
}

void draw_ep_vec3(nk_context* ctx, std::string name, glm::vec3 *v, int id)
{
	auto old_text = ctx->style.tab.text;
	ctx->style.tab.text = ctx->style.text.color;

	if (nk_tree_push_id(ctx, NK_TREE_NODE, name.c_str(), NK_MINIMIZED, id))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_property_float(ctx, "#x", -255, &(v->x), 255, 0.10, 0.10);
		nk_property_float(ctx, "#y", -255, &(v->y), 255, 0.10, 0.10);
		nk_property_float(ctx, "#z", -255, &(v->z), 255, 0.10, 0.10);
		nk_tree_pop(ctx);
	}
	ctx->style.tab.text = old_text;

}
/*
void draw_ep_vec3(nk_context* nctx, std::string name, glm::vec3 *v)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.25);

	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.75);


	if (nk_group_begin(nctx, "float_input_group", NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(nctx, 20, 3);
		nk_property_float(nctx, "#", -1000000, &v->x, 1000000, 0.10f, 0.1f);
		nk_property_float(nctx, "#", -1000000, &v->y, 1000000, 0.10f, 0.1f);
		nk_property_float(nctx, "#", -1000000, &v->z, 1000000, 0.10f, 0.1f);

		nk_group_end(nctx);
	}

	nk_layout_row_end(nctx);

}*/

void draw_ep_col3(nk_context* ctx, std::string name, glm::vec3 *v, int id)
{
	nk_colorf tempC;
	tempC.r = v->x;
	tempC.g = v->y;
	tempC.b = v->z;


	auto old_text = ctx->style.tab.text;
	auto old_max = ctx->style.tab.node_maximize_button.text_normal;
	auto old_min = ctx->style.tab.node_minimize_button.text_normal;
	ctx->style.tab.text = ctx->style.text.color;
	ctx->style.tab.node_maximize_button.text_normal = nk_rgb(v->x*255, v->y * 255, v->z * 255);
	ctx->style.tab.node_minimize_button.text_normal = nk_rgb(v->x * 255, v->y * 255, v->z * 255);


	if (nk_tree_push_id(ctx, NK_TREE_NODE, name.c_str(), NK_MINIMIZED, id))
	{
		nk_layout_row_dynamic(ctx, nk_window_get_content_region(ctx).w, 1);

		tempC = nk_color_picker(ctx, tempC, NK_RGB);

		nk_tree_pop(ctx);
	}

	v->x = tempC.r;
	v->y = tempC.g;
	v->z = tempC.b;


	ctx->style.tab.node_maximize_button.text_normal = old_max;
	ctx->style.tab.node_minimize_button.text_normal = old_min;

	ctx->style.tab.text = old_text;
}

void draw_ep_col3(nk_context* nctx, std::string name, glm::vec3 *v)
{
	nk_layout_row_begin(nctx, NK_DYNAMIC, 30, 2);
	nk_layout_row_push(nctx, 0.25);

	nk_label(nctx, name.c_str(), NK_TEXT_LEFT);

	nk_layout_row_push(nctx, 0.75);
	nk_colorf tempC;
	tempC.r = v->x;
	tempC.g = v->y;
	tempC.b = v->z;

	tempC = nk_color_picker(nctx, tempC, NK_RGB);//TODO: BULLSHIT

	v->x = tempC.r;
	v->y = tempC.g;
	v->z = tempC.b;
	nk_layout_row_end(nctx);

}