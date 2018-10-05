#pragma once
#include <ge/entity/component/Component.h>
#include <ge/graphics/types/Material.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>

namespace ge
{
    struct RuntimeMaterialComponent : public Component
    {
        RuntimeMaterialComponent(Entity*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
        Material* mat;
        bool shouldPut = false;
    private:
        static ComponentConstructorRegistry::StartupHook _hook;
    };
}
