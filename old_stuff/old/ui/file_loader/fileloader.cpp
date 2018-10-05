#include <ui/file_loader/fileloader.h>
#include "memory/GlobalMemory.h"
#include "util/ResourceUtil.h"
#include "graphics/meshes/debug/DebugVertexTriangleMesh.h"

#define TYPE_FILE 1
#define TYPE_FOLDER 2

namespace fs = std::experimental::filesystem;


FileLoader::FileLoader(nk_context* ctx, int *returnState, std::string *returnValue)
{
	ge::GlobalRuntime::ge_REGISTER_RUNTIME_HANDLER;

	ge::GlobalMemory::get("ge_update_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);
	ge::GlobalMemory::get("ge_uirender_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_INSERT_HEAP(this);

	this->returnState = returnState;
	this->returnValue = returnValue;

	this->ctx = ctx;
	newFolder("D:");
}

void FileLoader::render()
{

	if (nk_begin(ctx, "File Loader", nk_rect(350, 50, 430, 650),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE |
		NK_WINDOW_CLOSABLE | NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, std::string(currentDirectory).c_str(), NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 500, 1);

		if (nk_group_begin(ctx, "files", NK_WINDOW_BORDER)) { // column 1
			
			nk_layout_row_dynamic(ctx, 20, 1);

			if (nk_button_label(ctx, "..")) // Go Back Directory
			{
				currentDirectory = currentDirectory.substr(0, currentDirectory.length()-2);
				ge::ConsoleIO::print(currentDirectory+"\n");
				currentDirectory = currentDirectory.substr(0, currentDirectory.find_last_of('/'));
				newFolder("");
			}
			for(int i = 0; i < folders.size(); i++)
			{
				_fileItem file = folders[i];



				nk_layout_row_dynamic(ctx, 20, 1);
				if (file.second == TYPE_FOLDER)
				{
					ctx->style.button.hover = nk_style_item_color(nk_rgb(0, 51, 20));

					ctx->style.button.normal = nk_style_item_color(nk_rgb(51, 153, 102)); 
					ctx->style.button.text_normal = nk_color(nk_rgb(0, 0, 0));

					if (nk_button_label(ctx, file.first.c_str()))
					{
						newFolder(file.first);
					}
				}
				else if (file.second == TYPE_FILE)
				{

					ctx->style.button.hover = nk_style_item_color(nk_rgb(0, 70, 70));


					if (selectedItem != i)
					{
						ctx->style.button.normal = nk_style_item_color(nk_rgb(0, 102, 153));
						ctx->style.button.text_normal = nk_color(nk_rgb(0, 0, 0));

						if (nk_button_label(ctx, file.first.c_str()))
						{
							selectedItem = i;
						}
					}
					else if (selectedItem == i)
					{
						ctx->style.button.normal = nk_style_item_color(nk_rgb(0, 70, 70));
						ctx->style.button.text_normal = nk_color(nk_rgb(0, 0, 0));
						if (nk_button_label(ctx, file.first.c_str()));
					}
				}
				
				
			}
			ctx->style.button.normal = nk_style_item_color(nk_rgb(50, 50, 50));
			ctx->style.button.text_normal = nk_color(nk_rgb(175, 175, 175));
			ctx->style.button.hover = nk_style_item_color(nk_rgb(40, 40, 40));

			nk_group_end(ctx);
		}

		nk_layout_row_dynamic(ctx, 60, 2);
		if (nk_button_label(ctx, "Cancel"))
		{
			//Exit Window
			ge::GlobalMemory::get("ge_update_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_REMOVE_HEAP(this);
			ge::GlobalMemory::get("ge_uirender_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_REMOVE_HEAP(this);

			*returnState = 0; //have some state i.e. GE_SUCCESS

			delete this;
		}
		if (nk_button_label(ctx, "Done"))
		{
			if (selectedItem != -1)
			{
				//Return Value
				*returnState = 1; //have some state i.e. GE_SUCCESS
				*returnValue = currentDirectory + folders[selectedItem].first;

				
				ge::GlobalMemory::get("ge_update_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_REMOVE_HEAP(this);
				ge::GlobalMemory::get("ge_uirender_runtime_group").getRawData<ge::RuntimeGroup>()->ge_RUNTIME_GROUP_REMOVE_HEAP(this);

				delete this;
			}
		}
		nk_end(ctx);

		
	}

}

void FileLoader::update()
{
	/*for(auto folder : folders)
	{
		if(folder.isSelected)
		{
			
		}
	}*/
}

void FileLoader::setResource()
{
	currentDirectory = ge::ResourceUtil::getResPath("");
	currentDirectory = currentDirectory.substr(0, currentDirectory.length() - 1);
	newFolder("");
}


void FileLoader::newFolder(std::string folderName)
{
	selectedItem = -1;
	folders.clear();
	currentDirectory += folderName + "/";
	for (fs::path p : fs::directory_iterator(currentDirectory))
	{
		folders.push_back({ p.filename().string(), fs::is_directory(p) ? TYPE_FOLDER : TYPE_FILE });
	}

}
