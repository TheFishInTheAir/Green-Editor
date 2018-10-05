#pragma once
#include <ge/entity/component/Component.h>
//#include <ge/entity/component/ComponentConstructorRegistry.h>

namespace ge
{
    struct EngineControllerComponent : public Component
    {
        EngineControllerComponent(Entity* e) : Component(e){};
        
        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
    };
}
