#version 330

#pragma include <engine/global_settings.pre>

layout(location = VERTEX_POSITION) in vec3 vertexPositions;

uniform mat4 mvp;

void main()
{
  gl_Position = mvp * vec4(vertexPositions,1);
}
