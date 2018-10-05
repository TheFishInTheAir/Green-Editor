#pragma once
#include <ge/entity/component/Component.h>
#include <ge/graphics/meshes/TriangleMesh.h>
#include <ge/graphics/types/lights/LightPoint.h>
#include <ge/entity/component/components/TransformComponent.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>
#include <vector>
namespace ge
{
    struct PointLightComponent : public Component
    {
        PointLightComponent(Entity*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
        
        LightPoint light;
    private:
        bool debugBox = false;

        TransformComponent* transformComponent = nullptr;
        static ComponentConstructorRegistry::StartupHook _hook;

    };
}
