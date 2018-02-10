#version 330

#define VERTEX

#pragma include <engine/global_settings.pre>

layout(location = VERTEX_POSITION) in vec3 vertexPositions;
layout(location = NORMAL_POSITION) in vec3 normals;
layout(location = UV_POSITION) in vec2 UV;

out vec2 tUV;
out vec3 tNorm;
out vec3 tFragPos;
uniform mat4 MVP_M;
uniform mat4 MVP_VP;

void main()
{
	gl_Position = MVP_M_VP * vec4(vertexPositions, 1);
	tFragPos = vec3(MVP_M * vec4(vertexPositions, 1.0));
	tUV = UV;
	tNorm = mat3(transpose(inverse(MVP_M))) * normals;

}
