#version 330
layout(location = 0) in vec3 vertexPositions;

out vec3 posColour;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertexPositions,1);

    posColour = normalize(vertexPositions);
}
