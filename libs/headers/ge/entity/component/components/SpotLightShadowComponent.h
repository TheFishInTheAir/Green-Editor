#pragma once

#include <ge/entity/component/Component.h>
#include <ge/graphics/meshes/TriangleMesh.h>
#include <ge/graphics/types/lights/LightSpot.h>
#include <ge/entity/component/components/TransformComponent.h>
#include <ge/entity/component/components/SpotLightComponent.h>
#include <ge/graphics/types/lights/AngleShadow.h>
#include <ge/graphics/Camera.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>
#include <ge/graphics/pipeline/PipelineStage.h>

#include <ge/graphics/types/Texture.h>
#include <ge/graphics/types/FrameBuffer.h>
#include <vector>

namespace ge
{
    struct SpotLightShadowComponent : public Component
    {
        SpotLightShadowComponent(Entity*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
        
    private:
        Camera* cam;
        int shadowRes = 1;
        bool shouldUpdate = 0;
        PipelineStage *ps;
        FrameBuffer   *fb = nullptr;
        Texture       *tex = nullptr;
        AngleShadow   *shadow = nullptr;
        void genFB();


        SpotLightComponent* spotLightComponent = nullptr;
        TransformComponent* transformComponent = nullptr;
        static ComponentConstructorRegistry::StartupHook _hook;

    };
}