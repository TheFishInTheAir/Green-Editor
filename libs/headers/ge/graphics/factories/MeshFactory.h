//
// Created by Ethan Breit on 2017-07-29.
//

#pragma once

#include <graphics/meshes/TriangleMesh.h>

namespace ge
{
    struct MeshFactory
    {
        virtual TriangleMesh* newTriangleMesh() = 0;
		virtual TriangleMesh* newTriangleMesh(Empty::MeshData) = 0;
    };
}