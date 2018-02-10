#pragma once
#include "runtime/Runtime.h"
#include <engine/global_settings.pre>
#include "nuklear.h"
#include <filesystem>

struct FileLoader
{
	FileLoader(nk_context*, int *returnState, std::string *returnValue);

	void render();
	void update();

	void setResource();

	ge_START_CYCLE_HANDLER(FileLoader)
		ge_GENERATE_TRAMPOLINE(update, UPDATE)
		ge_GENERATE_TRAMPOLINE(render, 9)
		ge_END_CYCLE_HANDLER


private:

	int *returnState;
	std::string *returnValue;

	std::string currentDirectory = "";

	void newFolder(std::string);

	typedef std::pair<std::string, int> _fileItem;

	int selectedItem = -1;

	std::vector<_fileItem> folders;


	nk_context* ctx;
};
