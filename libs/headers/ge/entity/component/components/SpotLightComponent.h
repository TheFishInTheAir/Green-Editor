#pragma once
#include <ge/entity/component/Component.h>
#include <ge/graphics/meshes/TriangleMesh.h>
#include <ge/graphics/types/lights/LightSpot.h>
#include <ge/entity/component/components/TransformComponent.h>
#include <ge/graphics/Camera.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>
#include <vector>
namespace ge
{
    struct SpotLightComponent : public Component
    {
        SpotLightComponent(Entity*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
        
        LightSpot light;
    private:
        bool debugBox = false;
        bool castShadows = false;
        bool hasInitShadows = true;//BAD STUFF NOTE: TEMP
//Shadows
        void shadowCycle();
        Camera* cam;
        float shadowRes = 1;

        TransformComponent* transformComponent = nullptr;
        static ComponentConstructorRegistry::StartupHook _hook;

    };
}
