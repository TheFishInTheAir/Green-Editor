#version 330
out vec3 colour;
in vec3 posColour;
void main() {
	colour = posColour;
}
