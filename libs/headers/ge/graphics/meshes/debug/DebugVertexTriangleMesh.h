//
// Created by Ethan Breit on 2017-08-10.
//

#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include <graphics/GraphicsCore.h>
#include "graphics/meshes/TriangleMesh.h"

namespace ge
{

    struct DebugVertexTriangleMesh
    {

        DebugVertexTriangleMesh();

        TriangleMesh *_baseMesh;

        std::vector<float> vertices;
        std::vector<int> indices;

        glm::vec3 tint;

        void rebuffer();
        void render();

    private:
        GraphicsCore *_graphicsCore;

        Uniform *t;
        IndexBuffer *i;
        VertexBuffer *v;

    };

}