#include <ui/widgets/staticobject_widget.h>
#include "memory/GlobalMemory.h"
#include "engine/defaults/StaticObject.h"
#include <sstream>
#include "input/KeyboardHandler.h"
#include "glm/gtx/matrix_decompose.hpp"

StaticObjectWidget::StaticObjectWidget(nk_context* ctx)
{
	ge::GlobalRuntime::ge_REGISTER_RUNTIME_HANDLER;

	this->ctx = ctx;

	ge::GlobalMemory::get("ge_update_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);
	ge::GlobalMemory::get("ge_uirender_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);
	ge::GlobalMemory::get("ge_postrender_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);

}

void StaticObjectWidget::render()
{
	if (nk_begin(ctx, "Static Objects", nk_rect(350, 50, 430, 450),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE | NK_WINDOW_TITLE))
	{

		nk_layout_row_dynamic(ctx, 20, 1);
		if(nk_button_label(ctx, "Refresh"))
		{
			objs = ge::GlobalMemory::get(MSTR(GE_ENTITES_GM)).getRawData<std::forward_list<ge::StaticObject*>>();
			int tempCount = 0;
			for(auto obj : *objs)
			{
				tempCount++;
			}
			count = tempCount;
		}

		drawObjectGroup();



		nk_layout_row_dynamic(ctx, 20, 1);

		std::string dispStr;
		switch (translationMode)
		{
		case 0: dispStr = "Translate"; break;
		case 1: dispStr = "Rotate"; break;
		case 2: dispStr = "Scale"; break;

		}
		if (nk_combo_begin_label(ctx, dispStr.c_str(), nk_vec2(nk_widget_width(ctx), 200))) {
			nk_layout_row_dynamic(ctx, 25, 1);
			
			if (nk_combo_item_label(ctx, "Translate", NK_TEXT_LEFT))
				translationMode = 0;

			if (nk_combo_item_label(ctx, "Rotate", NK_TEXT_LEFT))
				translationMode = 1;

			if (nk_combo_item_label(ctx, "Scale", NK_TEXT_LEFT))
				translationMode = 2;
			nk_combo_end(ctx);
		}

		nk_layout_row_dynamic(ctx, 20, 1);
		
		nk_progress(ctx, &moveScale, 10*100, nk_true);
		nk_layout_row_dynamic(ctx, 10, 1);
		nk_label(ctx, (std::to_string(moveScale)+"%").c_str(), NK_TEXT_ALIGN_CENTERED);


		nk_end(ctx);
	}
	drawTransformData(); // Should not be in here

}

void StaticObjectWidget::update()
{
	static bool lBrackPress = false;
	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::LBRACK) && count != -1)
	{
		if (lBrackPress == false)
		{
			lBrackPress = true;
			if (selected == -1)
			{
				selected = count - 1;
			}
			else
			{
				int tempSelect = selected - 1;
				if (tempSelect < 0)
				{
					selected = count - 1;
				}
				else
				{
					selected = tempSelect;
				}

			}
		}
	}
	else
	{
		lBrackPress = false;
	}

	static bool rBrackPress = false;
	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::RBRACK) && count != -1)
	{
		if (rBrackPress == false)
		{
			rBrackPress = true;
			if (selected == -1)
			{
				selected = 0;
			}
			else
			{
				int tempSelect = selected + 1;
				if (tempSelect > count-1)
				{
					selected = 0;
				}
				else
				{
					selected = tempSelect;
				}

			}
		}
	}
	else
	{
		rBrackPress = false;
	}

	if (ge::KeyboardHandler::keyDownSticky(ge::KeyboardKey::NPDIV))
	{
		translationMode = 0;
	}

	if (ge::KeyboardHandler::keyDownSticky(ge::KeyboardKey::NPMULT))
	{
		translationMode = 1;
	}

	if (ge::KeyboardHandler::keyDownSticky(ge::KeyboardKey::NPMIN))
	{
		translationMode = 2;
	}

	if (selected != -1)
	{
		int i = 0;
		
		for (auto obj : *objs)
		{
			if (i == selected)
			{
				if (box != nullptr) {
					//glm::vec3 pos(obj->model.getMat()[3]);
					//box->model = glm::translate(pos);
					{
						
						float realScale = 0.0f;

						if (obj->model.scale.x <= obj->model.scale.y && obj->model.scale.x <= obj->model.scale.z)
							realScale = obj->model.scale.x;

						if (obj->model.scale.y <= obj->model.scale.x && obj->model.scale.y <= obj->model.scale.z)
							realScale = obj->model.scale.y;

						if (obj->model.scale.z <= obj->model.scale.x && obj->model.scale.z <= obj->model.scale.y)
							realScale = obj->model.scale.z;

						box->model = glm::translate(obj->model.pos);

						box->model = glm::scale(box->model, {realScale*2,realScale*2,realScale*2 });

					}

				}

				static int flashCount = 0;
				if(flashCount==30)
				{
					flashCount = 0;
					if(box->colour == glm::vec3(1,1,1))
						box->colour = { 0,0,0 };
					else
					{
						box->colour = { 1,1,1 };
					}

				}
				flashCount++;

				switch (translationMode)
				{
				case 0: move(obj); break;
				case 1: move(obj); break;
				case 2: scale(obj); break;
				}
			}
			i++;
		}
	}
}

void StaticObjectWidget::postRender()
{

	if(selected != -1)
	{
		int i = 0;

		for (auto obj : *objs)
		{
			if (i == selected) 
			{

				

				glDisable(GL_DEPTH_TEST);
				
				static bool f = false;
				if(!f)
				{
					f = true;
					ge::Camera* camera = ge::GlobalMemory::get(DBL_STRINGIFY(CURRENT_CAMERA)).getRawData<ge::Camera>();
					
					

					box = new ge::Debug::DebugColouredBox(camera);
					box->model = glm::translate(obj->model.pos);
					box->model = glm::scale(box->model, { 0.02,0.02,0.02 });
					box->colour = { 1,1,1 };
					
				}
				
				box->render();

				glEnable(GL_DEPTH_TEST);

			}
			
			i++;

		}
	}

}

void StaticObjectWidget::drawObjectGroup()
{
	nk_layout_row_dynamic(ctx, 300, 1);
	if (nk_group_begin(ctx, "objects", NK_WINDOW_BORDER)) { // column 1
		if (objs == nullptr)
			return;

		int i = 0;

		for (auto obj : *objs)
		{
			if (i == selected)
			{

				ctx->style.button.normal = nk_style_item_color(nk_rgb(0, 70, 70));
			}
			else
				ctx->style.button.normal = nk_style_item_color(nk_rgb(50, 50, 50));

			


			nk_layout_row_dynamic(ctx, 20, 1);
			if (nk_button_label(ctx, [](auto a)
			{
				std::stringstream ss;
				ss << std::hex << std::addressof(a);
				return ss.str().c_str();
			}(obj))) // Lambda
			{
				selected = i;
			}
			i++;
		}
		nk_group_end(ctx);
		ctx->style.button.normal = nk_style_item_color(nk_rgb(50, 50, 50));

	}
}

void StaticObjectWidget::drawTransformData()
{
	if (selected != -1)
	{
		int i = 0;

		for (auto obj : *objs)
		{
			if (i == selected && box )
			{
				static ge::Camera* currentCamera = ge::GlobalMemory::get(DBL_STRINGIFY(CURRENT_CAMERA)).getRawData<ge::Camera>();

				/*
				if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::I)) {
					int sizeOfVertBuf = obj->mesh->getVertexBuffer("vertex")->data->size;
					int sizePerVert = obj->mesh->getVertexBuffer("vertex")->data->sizePerAttrib;
					int vecs = sizeOfVertBuf / (sizePerVert * sizeof(float));
					for (int i = 0; i < vecs; i++)
					{
						const float* data = (float*)obj->mesh->getVertexBuffer("vertex")->data->data;

						glm::mat4 finMat = (currentCamera->vp); //* obj->model.getMat());
						glm::vec4 tempVec = glm::vec4(data[i * 3], data[i * 3 + 1], data[i * 3 + 2], 1);
						glm::vec4 modVec = obj->model.getMat() * tempVec;
						glm::vec4 finVec = finMat * modVec;
						//ge::ConsoleIO::print(std::string("pos:   ") + std::to_string((obj->model.getMat()[3] * glm::vec4((((glm::vec3*)data)[i]), 1)).x) + ", " + std::to_string((obj->model.getMat()[3] * glm::vec4((((glm::vec3*)data)[i]), 1)).y) + ", " + std::to_string((obj->model.getMat()[3] * glm::vec4((((glm::vec3*)data)[i]), 1)).z) + ", \n");
						if (finVec.w < 0)
							return;

						if (nk_begin(ctx, std::string("VData" + std::to_string(i)).c_str(), nk_rect(1920 * (((finVec.x / finVec.w) + 1) / 2), 1080 * ((1 - (finVec.y / finVec.w)) / 2), 300, 25), NK_WINDOW_NO_SCROLLBAR))
						{

							nk_layout_row_dynamic(ctx, 20, 1);
							nk_label(ctx, (std::string("pos:   ") + std::to_string(modVec.x) + ", " + std::to_string(modVec.y) + ", " + std::to_string(modVec.z) + ", ").c_str(), NK_TEXT_ALIGN_LEFT);

							nk_end(ctx);
						}
					}
				}*/
				/*
				glm::vec3 scale;
				glm::quat rotation;
				glm::vec3 translation;
				glm::vec3 skew;
				glm::vec4 perspective;
				glm::decompose(obj->model.getMat(), scale, rotation, translation, skew, perspective);

				glm::mat4 finMat = (currentCamera->vp); //* obj->model.getMat());
				glm::vec4 finVec = finMat * box->model[3];

				if (finVec.w < 0)
					return;

				if (nk_begin(ctx, "Transform Data", nk_rect(1920*(((finVec.x / finVec.w) + 1) / 2), 1080*((1 - (finVec.y / finVec.w)) / 2), 300, 70), NULL))
				{

					nk_layout_row_dynamic(ctx, 20, 1);
					nk_label(ctx, (std::string("pos:   ") + std::to_string(translation.x) + ", " + std::to_string(translation.y) + ", " + std::to_string(translation.z) + ", ").c_str(), NK_TEXT_ALIGN_LEFT);
					nk_layout_row_dynamic(ctx, 20, 1);
					nk_label(ctx, (std::string("scale: ") + std::to_string(obj->model.scale.x) + ", " + std::to_string(obj->model.scale.y) + ", " + std::to_string(scale.z) + ", ").c_str(), NK_TEXT_ALIGN_LEFT);

					nk_end(ctx);
				}*/
			}
			i++;
		}
	}

}

void StaticObjectWidget::move(ge::StaticObject* obj)
{

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP8))
	{
		//POSZ
		obj->model.pos += glm::vec3(0.0f, 0.0f, 0.1f) * glm::vec3(((float)moveScale) / 100.0f) / obj->model.scale;
	}
	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP2))
	{
		//NEGZ
		obj->model.pos += glm::vec3(0.0f, 0.0f, -0.1f) * glm::vec3(((float)moveScale) / 100.0f) / obj->model.scale;
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP4))
	{
		//POSX
		obj->model.pos += glm::vec3(0.1f, 0.0f, 0.0f) * glm::vec3(((float)moveScale) / 100.0f) / obj->model.scale;
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP6))
	{
		//NEGX
		obj->model.pos += glm::vec3(-0.1f, 0.0f, 0.0f) * glm::vec3(((float)moveScale) / 100.0f) / obj->model.scale;
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP7))
	{
		//POSY
		obj->model.pos += glm::vec3(0.0f, 0.1f, 0.0f) * glm::vec3(((float)moveScale) / 100.0f) / obj->model.scale;
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP9))
	{
		//NEGY
		obj->model.pos += glm::vec3(0.0f, -0.1f, 0.0f) * glm::vec3(((float)moveScale) / 100.0f) / obj->model.scale;
	}
}

void StaticObjectWidget::scale(ge::StaticObject* obj)
{



	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP8))
	{
		//POSZ
		obj->model.scale +=  glm::vec3( 1, 1, (obj->model.scale.z - (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.z );
	}
	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP2))
	{
		//NEGZ
		obj->model.scale += glm::vec3(1, 1, (obj->model.scale.z + (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.z );
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP4))
	{
		//POSX
		obj->model.scale += glm::vec3((obj->model.scale.x - (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.x, 1, 1 );
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP6))
	{
		//NEGX
		obj->model.scale += glm::vec3((obj->model.scale.x + (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.x, 1, 1 );
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP7))
	{
		//POSY
		obj->model.scale += glm::vec3(1, (obj->model.scale.y - (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.y, 1 );
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NP9))
	{
		//NEGY
		obj->model.scale += glm::vec3(1, (obj->model.scale.y + (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.y, 1 );
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NPADD))
	{
		//POS ALL
		obj->model.scale += glm::vec3((obj->model.scale.x + (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.x, (obj->model.scale.y + (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.y, (obj->model.scale.z + (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.z);
	}

	if (ge::KeyboardHandler::keyDown(ge::KeyboardKey::NPENTER))
	{
		//NEG ALL
		obj->model.scale += glm::vec3((obj->model.scale.x - (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.x, (obj->model.scale.y - (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.y, (obj->model.scale.z - (0.0025 * (float)moveScale / 100.0f)) / obj->model.scale.z);
	}

}

void StaticObjectWidget::rotate(ge::StaticObject*)
{
}
