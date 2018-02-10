#version 330
#pragma include "../global_settings.glsl"

layout(location = 0) in vec3 vertexPositions;

#ifndef NO_MVP

uniform mat4 mvp;

vec4 ge_mvp(vec4 _inVert, mat4 _mvp)
{

    return _mvp * _inVert;

}


#endif

void main()
{

    #ifndef NO_MVP

    #endif

    exec();
}