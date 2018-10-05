#pragma once
#include <ge/entity/component/Component.h>
#include <ge/graphics/meshes/TriangleMesh.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>

namespace ge
{
    struct MeshRendererComponent : public Component
    {
        MeshRendererComponent(Entity*);
        MeshRendererComponent(Entity*, TriangleMesh*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();
        
        TriangleMesh* mesh;
    private:
        void init();
        static ComponentConstructorRegistry::StartupHook _hook;

    };
}
