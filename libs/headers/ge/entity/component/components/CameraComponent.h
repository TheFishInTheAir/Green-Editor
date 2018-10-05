#pragma once
#include <ge/entity/component/Component.h>
#include <ge/graphics/Camera.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>
namespace ge
{
    struct TransformComponent;
    struct CameraComponent : public Component
    {
        CameraComponent(Entity* e);

        void defaultInit();
        void insertToDefaultBatch();

        void cycle();
        void destroy();
        std::string getTypeName();

        Camera camera;
        void makeDisplay();
    private:
        static ComponentConstructorRegistry::StartupHook _hook;
		bool shouldMakeDisplay = false;
        bool hasTransformComponent = false;
        TransformComponent* transformComponent;
    };

}
