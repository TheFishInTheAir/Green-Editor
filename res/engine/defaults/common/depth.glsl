#version 330

#pragma include <engine/global_settings.pre>

#ifdef VERTEX

layout(location = VERTEX_POSITION) in vec3 vpos;

uniform mat4 MVP_M;
uniform mat4 MVP_VP;

void main()
{
    gl_Position = MVP_M_VP * vec4(vpos, 1);
}

#elif defined FRAGMENT

out vec4 colour;

void main()
{
    //colour = vec4(gl_FragCoord.z);
}

#endif
