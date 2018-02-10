#version 330

#pragma include <engine/global_settings.pre>

uniform vec3 UNIFORM_SOLID_COL;

out vec3 colOut;
void main()
{
  colOut = UNIFORM_SOLID_COL;
}
