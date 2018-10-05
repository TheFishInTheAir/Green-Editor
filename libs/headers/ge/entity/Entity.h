#pragma once
#include <cstdint>
#include <unordered_map>
//#include <map>
#include <string>
#include <vector>


namespace ge
{
	struct EntityTag;
    struct Component;
    
	struct Entity
	{
		uint32_t id;

		std::string name;

		std::vector<EntityTag*> tags;
		std::unordered_map<std::string, Component*> components;
        
        template<class T=Component>
        T* getComponent(std::string s)
        {
            return (T*) components.at(s);
        }
        
        void insertComponent(Component*);
		void removeComponent(std::string);

		void registerToTag(EntityTag*);
        
		bool isDestroyed();
		void destroy();

	private:
		bool destroyed = false;
	};

}
