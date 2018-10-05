//
// Created by Ethan Breit on 2017-07-29.
//

#pragma once

#include <ge/graphics/factories/MeshFactory.h>

namespace ge
{
    namespace GL
    {
        struct MeshFactory : ge::MeshFactory
        {
            ge::TriangleMesh *newTriangleMesh();
			ge::TriangleMesh* newTriangleMesh(Empty::MeshData);
        };
    }
}
