#pragma once
#include <ge/entity/component/Component.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>

namespace ge
{
    struct TransformComponent;
    struct FreeCamControllerComponent : public Component
    {
        FreeCamControllerComponent(Entity* e);

        void defaultInit();
        void insertToDefaultBatch();

        void cycle();
        void destroy();
        std::string getTypeName();
        
        float moveSpeed = 35.0f;
        float lookSpeed = 15.0f;
        
        float sprintModif = 2;
        
        
    private:
        static ComponentConstructorRegistry::StartupHook _hook;

		bool hasCamComponent = false;
        bool hasTransformComponent = false;
        TransformComponent* tComp = nullptr;
        
        float horizontalAngle = 0;
        float verticalAngle = 0;
    };
}
