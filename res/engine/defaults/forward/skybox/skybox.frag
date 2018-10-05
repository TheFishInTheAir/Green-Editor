#version 330

#define FRAGMENT

#pragma include <engine/global_settings.pre>

out vec4 outColour;

in vec3 texCoords;

uniform samplerCube SKYBOX;

void main()
{

	outColour = texture(SKYBOX, texCoords);
    //outColour = vec4(1);
}
