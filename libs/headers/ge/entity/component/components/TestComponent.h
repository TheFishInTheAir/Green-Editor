#pragma once
#include <ge/entity/component/Component.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>

namespace ge
{
    struct TestComponent : public ge::Component
    {
        TestComponent(Entity* e) : Component(e){};
        
        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
        
    private:
        int i = 0;
        static ComponentConstructorRegistry::StartupHook _hook;

    };
}
