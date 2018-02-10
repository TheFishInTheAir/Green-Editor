//
// Created by Ethan Breit on 2017-08-10.
//

#pragma once

namespace ge
{
    struct ColouredTriangleMesh
    {
        BaseTriangleMesh *_baseMesh;

        float vertices;
        float vertexColours; //TODO: FINISH

        void rebuffer();
        void render();

    };
}