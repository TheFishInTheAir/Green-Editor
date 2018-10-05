#version 330

#pragma include <engine/global_settings.pre>

#ifdef VERTEX

layout(location = VERTEX_POSITION) in vec3 vpos;
layout(location = UV_POSITION)     in vec2 texcoord;

out vec2 tTexcoord;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vpos, 1);
    tTexcoord   = texcoord;
}

#elif defined FRAGMENT

out vec4 colour;

in vec2 tTexcoord;

uniform sampler2D ALBEDO_REF;

void main()
{
    //colour = vec4(1,0,1,1);
    colour = texture(ALBEDO_REF, tTexcoord);
}

#endif
