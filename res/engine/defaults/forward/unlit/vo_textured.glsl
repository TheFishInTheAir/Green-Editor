#version 330

#pragma include <engine/global_settings.pre>
//NOTE: this is literally only for rendering a texture on a plane...
#ifdef VERTEX

layout(location = VERTEX_POSITION) in vec3 vpos;

out vec2 tTexcoord;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vpos, 1);
    tTexcoord   = (vpos.xy)+0.5f; //BECAUSE DUMB SHIT
}

#elif defined FRAGMENT

out vec4 colour;

in vec2 tTexcoord;

uniform sampler2D ALBEDO_REF;

void main()
{
    //colour = vec4(1,0,1,1);
    colour = vec4(texture(ALBEDO_REF, tTexcoord).xyz, 1);
}

#endif
