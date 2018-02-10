#version 330
layout(location = 0) in vec3 vertexPositions;
layout(location = 2) in vec2 UV;

out vec2 tUV;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * vec4(vertexPositions, 1);
	tUV = UV;
}
