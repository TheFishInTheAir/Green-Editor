#pragma once
#include <ge/entity/component/Component.h>
#include <ge/entity/component/components/TransformComponent.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>
#include <vector>

namespace ge
{
    struct AudioListinerComponent : public Component
    {
        AudioListinerComponent(Entity*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
        
    private:
    

        TransformComponent* transformComponent = nullptr;
        static ComponentConstructorRegistry::StartupHook _hook;

    };
}
