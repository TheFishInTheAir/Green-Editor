#pragma once
#include <string>
#include <list>

//#define TEST


namespace ge
{
	struct Entity;

	struct EntityTag
	{
		EntityTag();
		EntityTag(std::string);

		std::string name;

		std::list<Entity*> entities;

		//TODO: add insertion and removal

	};
}
