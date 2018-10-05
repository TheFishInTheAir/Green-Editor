#pragma once
#include "runtime/Runtime.h"
#include <engine/global_settings.pre>
#include "nuklear.h"
#include <filesystem>

struct FileLoader
{
	FileLoader(nk_context*, bool isRes, bool canCreate, void(*)(std::string));

	void render();

	bool isFinished();

private:

	int *returnState;
	std::string *returnValue;

	std::string currentDirectory = "";

	bool canCreate = false;

	void newFolder(std::string);

	typedef std::pair<std::string, int> _fileItem;

	int selectedItem = -1;

	void(*callback)(std::string);

	std::vector<_fileItem> folders;

	bool finished = false;

	nk_context* ctx;

	bool newFileDialogue = false;
	std::string newFileDialogueText;
};
