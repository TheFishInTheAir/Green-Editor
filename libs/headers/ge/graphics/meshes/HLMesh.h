#pragma once
#include <ge/graphics/types/Material.h>
#include <ge/graphics/empty_types/MeshData.h>
#include <ge/graphics/meshes/TriangleMesh.h>

namespace ge
{
    struct HLMesh
    {
        HLMesh();
        ~HLMesh();

        void render();

        void setMeshData(std::string); //TODO: REFACTOR, they aren't empty, that was a dumb naming thing... call them cold or something, it sounds cooler
        TriangleMesh* getMesh();

        void setMaterial(std::string);
        Material getMaterial();

        void destroy();

    private:
        Material mat;
        TriangleMesh* mesh = nullptr;

        void applyMat();

    };
}