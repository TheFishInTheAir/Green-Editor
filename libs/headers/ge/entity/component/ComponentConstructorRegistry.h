#pragma once
#include <ge/entity/component/Component.h>
#include <ge/entity/Entity.h>
#include <list>
namespace ge
{
    namespace ComponentConstructorRegistry
    {
        //usage: ComponentConstructorRegistry::StartupHook TestComponent::_hook("TestComponent", testComponentCreationFactor);
        struct StartupHook { StartupHook(std::string name, Component*(*)(Entity*)); }; 
        
        bool componentExists(std::string);
        Component* newComponent(std::string, Entity*);

        std::list<std::string> getAvailable();
    }
}