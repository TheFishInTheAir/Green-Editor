#include <resource_interface.h>
#include <util.h>
#include <custom_property_widgets.h>
#include <inspector.h>
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include <nuklear.h>

#include <glm/glm.hpp>


#include <ge/console/Log.h>
#include <ge/graphics/GraphicsCore.h>
#include <ge/entity/EntityManager.h>
#include <ge/entity/Entity.h>
#include <ge/entity/component/Component.h>
#include <ge/entity/component/ComponentBatch.h>
#include <ge/graphics/abs/OpenGL/types/GLTexture.h>
#include <ge/engine/scene/Scene.h>
#include <fileloader.h>
#include <ge/input/KeyboardHandler.h>
#include <ge/input/MouseHandler.h>
#include <ge/graphics/abs/OpenGL/meshes/GLTriangleMesh.h>
#include <ge/default_geom/Cube.h>
#include <ge/loader/LoadShader.h>
#include <ge/util/ResourceUtil.h>
#include <ge/loader/LoadMesh.h>
#include <ge/loader/LoadImage.h>
#include <ge/loader/LoadMaterial.h>
#include <ge/entity/component/components/TransformComponent.h>
#include <ge/entity/component/components/HLMeshComponent.h>
#include <ge/graphics/Camera.h>

#define RESOURCE_INTERFACE_SELECTED_SELECTOR_TABS	0
#define RESOURCE_INTERFACE_SELECTED_MESHES			1
#define RESOURCE_INTERFACE_SELECTED_TEXTURES		2
#define RESOURCE_INTERFACE_SELECTED_MATERIALS		3
#define RESOURCE_INTERFACE_SELECTED_AUDIOCLIPS		4
#define RESOURCE_INTERFACE_SELECTED_SHADERGROUPS	5

typedef struct
{
	uint8_t selected_resource = 0;
	FileLoader* fileloader = nullptr;
} resource_interface_context;
resource_interface_context* ric = nullptr;


//MESH
void add_mesh_callback(std::string raw_url)
{
	std::string res_path = ge::ResourceUtil::getResPath("");
	std::string url = raw_url.substr(res_path.length(), raw_url.length() - res_path.length());

	ge::Empty::MeshData* md = new ge::Empty::MeshData();
	ge::MeshLoader::loadTriangleMesh(url, md);
	ge::Scene::currentScene->meshes[url] = std::shared_ptr<ge::Empty::MeshData>(md);
}

void mesh_inspection_func(nk_context* ctx, void* meta)
{
	//NOTE: there should be a title but shhhh......

	ge::Empty::MeshData* meshData = (ge::Empty::MeshData*) meta;
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, "NOTE: it should be a material not a shadergroup", NK_TEXT_LEFT);
	nk_label(ctx, (std::string("Has Indicies: ")+(meshData->hasIndexBuffer ? "true" : "false")).c_str(), NK_TEXT_LEFT);
	nk_label(ctx, (std::string("Has Default ShaderGroup: ") + (meshData->hasShaderGroup ? "true" : "false")).c_str(), NK_TEXT_LEFT); //NOTE: this should be a material not a shader group...
	
	if(nk_tree_push(ctx, NK_TREE_TAB, "Vertex Buffers", NK_MINIMIZED))
	{
		int i = 0;
		for (auto vbo : meshData->vertexBuffers)
		{
			if (nk_tree_push_id(ctx, NK_TREE_TAB, vbo.second.c_str(), NK_MINIMIZED, i++))
			{
				nk_label(ctx, std::string("Total Verticies: " + std::to_string(vbo.first->size / (vbo.first->sizePerAttrib * 4))).c_str(), NK_TEXT_LEFT);

				nk_label(ctx, std::string("Elements Per Vertex: " + std::to_string(vbo.first->sizePerAttrib)).c_str(), NK_TEXT_LEFT);
				nk_label(ctx, std::string("Total Size: " + std::to_string(vbo.first->size) + " bytes").c_str(), NK_TEXT_LEFT);


				nk_tree_pop(ctx);
			}
		}
		nk_tree_pop(ctx);
	}
	if (meshData->hasIndexBuffer)
	{
		if(nk_tree_push(ctx, NK_TREE_TAB, "Index Buffer", NK_MINIMIZED))
		{
			nk_label(ctx, std::string("Total Indicies: " + std::to_string(meshData->indexBuffer->length)).c_str(), NK_TEXT_LEFT);
			nk_label(ctx, std::string("Total Size: " + std::to_string(meshData->indexBuffer->size) + " bytes").c_str(), NK_TEXT_LEFT);

			nk_tree_pop(ctx);
		}
	}
}

void draw_res_meshes(nk_context* ctx)
{
	nk_layout_row_dynamic(ctx, 15, 1);
	if (nk_button_label(ctx, "..."))
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_SELECTOR_TABS;
		return;
	}
	if (nk_button_label(ctx, "Add Mesh"))
	{
		ric->fileloader = new FileLoader(ctx, true, false, add_mesh_callback);
		return;
	}
	nk_layout_row_dynamic(ctx, 100, 8);
	for (auto mesh : ge::Scene::currentScene->meshes)
	{
		auto bounds = nk_widget_bounds(ctx);
		if (nk_button_label(ctx, mesh.first.c_str()))
		{
			set_inspection_content(mesh_inspection_func, mesh.second.get());
		}

		if (nk_contextual_begin(ctx, 0, nk_vec2(100, 300), bounds)) 
		{
			nk_layout_row_dynamic(ctx, 30, 1);

			if (nk_button_label(ctx, "Create Entity"))
			{
				ge::Camera* c = ge::Camera::displayCamera;

				ge::Entity* new_ent = new ge::Entity();
				ge::TransformComponent* tc = new ge::TransformComponent(new_ent);
				ge::HLMeshComponent*	mc = new ge::HLMeshComponent(new_ent);

				new_ent->name = mesh.first;

				new_ent->insertComponent(tc);
				new_ent->insertComponent(mc);

				*((glm::vec3*) tc->publicVars["Position"].second) = c->pos + (glm::vec3(c->dir.x, -c->dir.y, c->dir.z)*3);
				tc->reCalc();
				mc->setMeshData(mesh.first);
				mc->setMaterial(ge::Scene::currentScene->materials.begin()->first);
				tc->insertToDefaultBatch();
				mc->insertToDefaultBatch();

				ge::EntityManager::registerEntity(new_ent);
			}

			/*
			nk_layout_row_dynamic(ctx, 25, 1);
			//nk_checkbox_label(ctx, "Menu", &show_menu);
			nk_progress(ctx, &prog, 100, NK_MODIFIABLE);
			nk_slider_int(ctx, 0, &slider, 16, 1);
			//	show_app_about = nk_true;
			//nk_selectable_label(ctx, select[0] ? "Unselect" : "Select", NK_TEXT_LEFT, &select[0]);
			//nk_selectable_label(ctx, select[1] ? "Unselect" : "Select", NK_TEXT_LEFT, &select[1]);
			//nk_selectable_label(ctx, select[2] ? "Unselect" : "Select", NK_TEXT_LEFT, &select[2]);
			//nk_selectable_label(ctx, select[3] ? "Unselect" : "Select", NK_TEXT_LEFT, &select[3]);*/
			nk_contextual_end(ctx);
		}
	}
}

//TEXTURES
void add_tex_callback(std::string raw_url)
{
	std::string res_path = ge::ResourceUtil::getResPath("");
	std::string url = raw_url.substr(res_path.length(), raw_url.length() - res_path.length());
	
	auto img = std::shared_ptr<ge::Image>(new ge::Image());
	ge::ImageLoader::loadImage(url, &img);
	ge::Texture* texture;
	ge::GraphicsCore::ctx->textureFactory->genTexture(*img, &texture);
	texture->setFiltering(ge::TextureFilterType::Anisotropic_16x);
	//ge::MeshLoader::loadTriangleMesh(url, md);
	ge::Scene::currentScene->textures[url] = std::shared_ptr<ge::Texture>(texture);
}

void tex_inspection_func(nk_context* ctx, void* meta)
{
	//NOTE: there should be a title but shhhh......

	ge::GL::Texture* tex = (ge::GL::Texture*) meta;
	nk_layout_row_dynamic(ctx, 20, 1);
	nk_label(ctx, std::string("Title: " + tex->url).c_str(), NK_TEXT_LEFT);
	nk_label(ctx, (std::string("Width:  ") + std::to_string(tex->getWidth())).c_str(), NK_TEXT_LEFT);
	nk_label(ctx, (std::string("Height: ") + std::to_string(tex->getHeight())).c_str(), NK_TEXT_LEFT);
	switch (tex->getColourModel())
	{
	case ge::ColourModelType::BW:
		nk_label(ctx, (std::string("Colour Model: BlackWhite")).c_str(), NK_TEXT_LEFT);
		break;
	case ge::ColourModelType::RGB:
		nk_label(ctx, (std::string("Colour Model: RGB")).c_str(), NK_TEXT_LEFT);
		break;
	case ge::ColourModelType::RGBA:
		nk_label(ctx, (std::string("Colour Model: RGBA")).c_str(), NK_TEXT_LEFT);
		break;
	case ge::ColourModelType::ARGB:
		nk_label(ctx, (std::string("Colour Model: ARGB")).c_str(), NK_TEXT_LEFT);
		break;
	}

	switch (tex->getFiltering())
	{
	case ge::TextureFilterType::Nearest_Neighbour:
		nk_label(ctx, (std::string("Texture Filtering: Nearest Neighbor")).c_str(), NK_TEXT_LEFT);
	case ge::TextureFilterType::Bilinear:
		nk_label(ctx, (std::string("Texture Filtering: Bilinear")).c_str(), NK_TEXT_LEFT);
	case ge::TextureFilterType::Anisotropic_4x:
		nk_label(ctx, (std::string("Texture Filtering: Anisotropic 4x")).c_str(), NK_TEXT_LEFT);
	case ge::TextureFilterType::Anisotropic_8x:
		nk_label(ctx, (std::string("Texture Filtering: Anisotropic 8x")).c_str(), NK_TEXT_LEFT);
	case ge::TextureFilterType::Anisotropic_16x:
		nk_label(ctx, (std::string("Texture Filtering: Anisotropic 16x")).c_str(), NK_TEXT_LEFT);
	}
	nk_layout_row_dynamic(ctx, nk_window_get_content_region(ctx).w, 1);

	nk_image(ctx, nk_image_id(tex->id));
	
	//nk_label(ctx, (std::string("Has Default ShaderGroup: ") + (meshData->hasShaderGroup ? "true" : "false")).c_str(), NK_TEXT_LEFT); //NOTE: this should be a material not a shader group...

}

void draw_res_textures(nk_context* ctx)
{
	nk_layout_row_dynamic(ctx, 15, 1);
	if (nk_button_label(ctx, "..."))
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_SELECTOR_TABS;
		return;
	}
	if (nk_button_label(ctx, "Add Texture"))
	{
		ric->fileloader = new FileLoader(ctx, true, false, add_tex_callback);
		return;
	}
	nk_layout_row_dynamic(ctx, 100, 8);
	for (auto tex : ge::Scene::currentScene->textures)
	{
		if (nk_button_label(ctx, tex.first.c_str()))
		{
			set_inspection_content(tex_inspection_func, tex.second.get());
		}
	}
}

//MATERIALS
void add_mat_callback(std::string raw_url)
{
	std::string res_path = ge::ResourceUtil::getResPath("");
	std::string url = raw_url.substr(res_path.length(), raw_url.length() - res_path.length());

	ge::Material* mat = new ge::Material();
	*mat = ge::MaterialLoader::loadMaterial(url, true);
	if (ge::Scene::currentScene->materials.count(mat->shader_group) == 0)
	{
		ge::Log::err("resource_interface", "Early Exit Loading material, shadergroup not loaded: '"+mat->shader_group+"'");
		return;
	}
	ge::Scene::currentScene->materials[mat->name] = *mat;
	/*
	auto img = std::shared_ptr<ge::Image>(new ge::Image());
	ge::ImageLoader::loadImage(url, &img);
	ge::Texture* texture;
	ge::GraphicsCore::ctx->textureFactory->genTexture(*img, &texture);
	texture->setFiltering(ge::TextureFilterType::Anisotropic_16x);
	//ge::MeshLoader::loadTriangleMesh(url, md);
	ge::Scene::currentScene->textures[url] = std::shared_ptr<ge::Texture>(texture);*/
}

void new_mat_callback(std::string raw_url)
{/*
	std::string res_path = ge::ResourceUtil::getResPath("");
	std::string url = raw_url.substr(res_path.length(), raw_url.length() - res_path.length());

	auto img = std::shared_ptr<ge::Image>(new ge::Image());
	ge::ImageLoader::loadImage(url, &img);
	ge::Texture* texture;
	ge::GraphicsCore::ctx->textureFactory->genTexture(*img, &texture);
	texture->setFiltering(ge::TextureFilterType::Anisotropic_16x);
	//ge::MeshLoader::loadTriangleMesh(url, md);
	ge::Scene::currentScene->textures[url] = std::shared_ptr<ge::Texture>(texture);*/
}

void mat_inspection_func(nk_context* ctx, void* meta)
{
	std::string str = std::string(*((std::string*) meta));
	ge::Material read_only_mat = ge::Scene::currentScene->currentScene->materials[str];
	nk_layout_row_dynamic(ctx, 30, 1);
	//nk_label(ctx, std::string("TEST: " + str).c_str(), NK_TEXT_LEFT);

	nk_label(ctx, std::string("Name: " + read_only_mat.name).c_str(), NK_TEXT_LEFT);
	nk_label(ctx, std::string("URL: " + read_only_mat.url).c_str(), NK_TEXT_LEFT);
	{
		std::string shader_group = read_only_mat.shader_group;
		draw_ep_auto(ctx, "Shader Group", ge::DataType::SHADER_GROUP, &shader_group, 0);
		if (shader_group != read_only_mat.shader_group) //NOTE: there is more involved in changing shader group here...
			ge::Scene::currentScene->currentScene->materials[str].shader_group = shader_group;
	}

	for (int i = 0; i < read_only_mat.textures.size(); i++)
	{
		auto tex = read_only_mat.textures[i];

		nk_layout_row_dynamic(ctx, 30, 1);
		{
			std::string old_tex = tex.second.first;
			draw_ep_auto(ctx, tex.first, ge::DataType::TEXTURE, &old_tex, 1);
			if (old_tex != tex.second.first)
				ge::Scene::currentScene->currentScene->materials[str].textures[i].second.first = old_tex;

		}
		//nk_label(ctx, std::string(tex.second.first).c_str(), NK_TEXT_LEFT);

		ge::GL::Texture* gl_tex = (ge::GL::Texture*) ge::Scene::currentScene->textures[tex.second.first].get();
		nk_layout_row_dynamic(ctx, nk_window_get_content_region(ctx).w, 1);
		nk_image(ctx, nk_image_id(gl_tex->id));


	}

	//nk_label(ctx, "TEST TEST TEST TEST TTEST TEST TEST TEST", NK_TEXT_LEFT); //NOTE: this should be a material not a shader group...

}

void draw_res_materials(nk_context* ctx)
{
	nk_layout_row_dynamic(ctx, 15, 1);
	if (nk_button_label(ctx, "..."))
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_SELECTOR_TABS;
		return;
	}
	nk_layout_row_dynamic(ctx, 15, 2);
	if (nk_button_label(ctx, "Add Material"))
	{
		ric->fileloader = new FileLoader(ctx, true, false, add_mat_callback);
		return;
	}
	if (nk_button_label(ctx, "New Material"))
	{
		ric->fileloader = new FileLoader(ctx, true, true, add_mat_callback);
		return;
	}
	nk_layout_row_dynamic(ctx, 100, 8);
	for (auto mat : ge::Scene::currentScene->materials)
	{
		if (nk_button_label(ctx, mat.first.c_str()))
		{
			//if (get_current_inspection_meta() != nullptr)
				//nvm fuck
			//	return;
			set_inspection_content(mat_inspection_func, new std::string(mat.second.name), true);
		}
	}
}


//GENERAL TABS
void draw_resource_type_tabs(nk_context* ctx)
{

	nk_layout_row_dynamic(ctx, 100, 8);
	if (nk_button_label(ctx, "Meshes"))
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_MESHES;
	}
	if (nk_button_label(ctx, "Textures")) //NOTE: includes Cubemaps
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_TEXTURES;
	}
	if (nk_button_label(ctx, "Materials"))
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_MATERIALS;
	}
	if (nk_button_label(ctx, "AudioClips"))
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_AUDIOCLIPS;
	}
	if (nk_button_label(ctx, "ShaderGroups"))
	{
		ric->selected_resource = RESOURCE_INTERFACE_SELECTED_SHADERGROUPS;
	}
}

void draw_resource_interface(nk_context* ctx)
{
	if (ric == nullptr)
		ric = new resource_interface_context();
	if (nk_begin(ctx, "Resource Interface", getRelativeRect_WIN(0.15f, 0.8, 0.7f, 0.2f), NK_WINDOW_BORDER))
	{
		switch (ric->selected_resource)
		{
		case RESOURCE_INTERFACE_SELECTED_SELECTOR_TABS:
			draw_resource_type_tabs(ctx);
			break;
		case RESOURCE_INTERFACE_SELECTED_MESHES:
			draw_res_meshes(ctx);
			break;
		case RESOURCE_INTERFACE_SELECTED_TEXTURES:
			draw_res_textures(ctx);
			break;
		case RESOURCE_INTERFACE_SELECTED_MATERIALS:
			draw_res_materials(ctx);
			break;
		}
		nk_end(ctx);
	}

	if (ric->fileloader != nullptr)
		if (!ric->fileloader->isFinished())
			ric->fileloader->render();

}