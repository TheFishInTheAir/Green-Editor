#pragma once
#include <ge/graphics/meshes/TriangleMesh.h>
#include <ge/entity/Entity.h>
namespace ge
{
    namespace UniformAutomator
    {
        void initUniformSetup(ge::TriangleMesh*);
        void cycledUniformSetup(ge::TriangleMesh*);
        void cycledEntUniformSetup(ge::Entity*, ge::TriangleMesh*);

    }



}