#version 330


#define VERTEX

#pragma include <ge/engine/global_settings.pre>

layout(location = VERTEX_POSITION) in vec3 vertexPositions;

out vec3 texCoords;
out vec3 worldPos;

uniform mat4 MVP_M;
uniform mat4 MVP_VP;
void main()
{
	gl_Position = MVP_M_VP * vec4(vertexPositions, 1);

	worldPos = (MVP_M * vec4(vertexPositions, 1)).xyz;

}
