#pragma once
#include <ge/entity/component/Component.h>
#include <ge/graphics/meshes/HLMesh.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>

namespace ge
{
    struct PipelineStage;
    struct HLMeshComponent : public Component
    {
        HLMeshComponent(Entity*);
        HLMeshComponent(Entity*, HLMesh*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void cycle();
        void destroy();
        std::string getTypeName();

        void setMeshData(std::string);
        void setMaterial(std::string);
        
        HLMesh* mesh;

    private:
        void init();
        void meshUpdate();
        void uniforms(PipelineStage*);
        std::string sketchMatTag = "NULL";
        std::string sketchMeshTag = "NULL";


        std::string sketchCachedMatTag = sketchMatTag;
        std::string sketchCachedMeshTag = sketchMeshTag;


        static ComponentConstructorRegistry::StartupHook _hook;
    };
}
