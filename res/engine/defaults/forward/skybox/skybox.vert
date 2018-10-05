#version 330


#define VERTEX

#pragma include <engine/global_settings.pre>

layout(location = VERTEX_POSITION) in vec3 vertexPositions;

out vec3 texCoords;

uniform mat4 MVP_V;
uniform mat4 MVP_P;

void main()
{
	vec4 pos = MVP_P * mat4(mat3(MVP_V)) * vec4(vertexPositions, 1);

	gl_Position = vec4(pos.x,pos.y,pos.w,pos.w);

	texCoords = vertexPositions;

}
