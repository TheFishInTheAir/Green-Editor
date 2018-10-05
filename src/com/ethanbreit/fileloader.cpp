#include <fileloader.h>
#include "util/ResourceUtil.h"

#define TYPE_FILE 1
#define TYPE_FOLDER 2

#ifdef WIN32
#define FL_SEP_CHAR '\\'
#else
#define FL_SEP_CHAR '/'
#endif

namespace fs = std::experimental::filesystem;


FileLoader::FileLoader(nk_context* ctx, bool isRes, bool canCreate, void(*callback)(std::string))
{

	this->ctx = ctx;
	this->callback = callback;
	this->canCreate = canCreate;

	if (isRes)
		newFolder(ge::ResourceUtil::getResPath(""));
	else
		newFolder("D:"+FL_SEP_CHAR);
}

void FileLoader::render()
{

	if (nk_begin(ctx, "File Loader", nk_rect(350, 50, 430, 650),
		NK_WINDOW_BORDER | NK_WINDOW_MOVABLE |
		NK_WINDOW_TITLE))
	{
		nk_layout_row_dynamic(ctx, 20, 1);
		nk_label(ctx, std::string(currentDirectory).c_str(), NK_TEXT_LEFT);
		nk_layout_row_dynamic(ctx, 500, 1);

		auto b_norm_old = ctx->style.button.normal;
		auto b_tnorm_old = ctx->style.button.text_normal;
		auto b_hov_old = ctx->style.button.hover;

		if (nk_group_begin(ctx, "files", NK_WINDOW_BORDER)) { // column 1

			nk_layout_row_dynamic(ctx, 20, 1);

			if (nk_button_label(ctx, "..")) // Go Back Directory
			{
				currentDirectory = currentDirectory.substr(0, currentDirectory.length() - 2);
				//ge::ConsoleIO::print(currentDirectory + "\n");
				currentDirectory = currentDirectory.substr(0, currentDirectory.find_last_of(FL_SEP_CHAR));
				newFolder("");
			}
			for (int i = 0; i < folders.size(); i++)
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
						newFolder(file.first+FL_SEP_CHAR);
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
			ctx->style.button.normal = b_norm_old;
			ctx->style.button.text_normal = b_tnorm_old;
			ctx->style.button.hover = b_hov_old;

			nk_group_end(ctx);
		}
		if (canCreate)
		{
			nk_layout_row_dynamic(ctx, 30, 1);
			if (nk_button_label(ctx, "New File"))
				newFileDialogue = true;
		}
		nk_layout_row_dynamic(ctx, 30, 2);
		if (nk_button_label(ctx, "Cancel"))
		{
			finished = true;
		}
		if (nk_button_label(ctx, "Done"))
		{
			if (selectedItem != -1)
			{
				//Return Value
				//*returnState = 1; //have some state i.e. GE_SUCCESS
				//*returnValue = currentDirectory + folders[selectedItem].first;
				callback(currentDirectory + folders[selectedItem].first);

				finished = true;
			}
		}
		nk_end(ctx);
	}

	if (newFileDialogue)
	{
		if (nk_begin(ctx, "New File", nk_rect(500, 500, 250, 125), NK_WINDOW_MOVABLE | NK_WINDOW_BORDER | NK_WINDOW_TITLE))
		{
			nk_layout_row_dynamic(ctx, 30, 1);
			{
				char* editStr = (char*)malloc(newFileDialogueText.size() + 2);
				strcpy(editStr, newFileDialogueText.c_str());
				nk_edit_string_zero_terminated(ctx, NK_EDIT_SIMPLE, editStr, 64, 0);
				newFileDialogueText = std::string(editStr);
				free(editStr);
			}

			nk_layout_row_dynamic(ctx, 40, 2);
			if (nk_button_label(ctx, "Cancel"))
			{
				newFileDialogue = false;
			}
			if (nk_button_label(ctx, "Done"))
			{
				std::fstream fstr;
				fstr.open(currentDirectory+newFileDialogueText, std::ios::out);
				fstr.close();
				newFolder("");  //refresh
				//TODO: CREATE THE FILE
				newFileDialogue = false;
			}
			nk_end(ctx);
		}
	}
}

bool FileLoader::isFinished()
{
	return finished;
}


//void FileLoader::setResource()
//{
//	currentDirectory = ge::ResourceUtil::getResPath("");
//	currentDirectory = currentDirectory.substr(0, currentDirectory.length() - 1);
//	newFolder("");
//}


void FileLoader::newFolder(std::string folderName)
{
	selectedItem = -1;
	folders.clear();
	currentDirectory += folderName;// +FL_SEP_CHAR;
	for (fs::path p : fs::directory_iterator(currentDirectory))
	{
		folders.push_back({ p.filename().string(), fs::is_directory(p) ? TYPE_FOLDER : TYPE_FILE });
	}

}
