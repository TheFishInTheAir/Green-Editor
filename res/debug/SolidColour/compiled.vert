#version 330

#ifndef GLOBAL_SETTINGS 
#define GLOBAL_SETTINGS
//Rendder IDs
#define RENDER 0

#define PRE_RENDER 1
#define POST_RENDER 2

#define UPDATE 3

#define LOADER 6

//STANDARD VERTEX ATTRIBUTES
#define VERTEX_POSITION 0
#define NORMAL_POSITION 1
#define UV_POSITION     2

//STANDARDS
#define FRAG_OUT_COL ge_fragment_colour
#define CAMERA_DIR   ge_camera_direction

//LIGHTING

#define MAX_POINT_LIGHTS	   	16
#define MAX_SPOT_LIGHTS			8
#define MAX_DIRECTIONAL_LIGHTS	1

//UNIFORMS

//IN

#define UNIFORM_POINT_LIGHTS_IN			ge_point_lights_in
#define UNIFORM_SPOT_LIGHTS_IN			ge_spot_lights_in
#define UNIFORM_DIRECTIONAL_LIGHTS_IN	ge_directional_lights_in

//TRANSFER

#define UNIFORM_POINT_LIGHTS_T			ge_point_lights_t
#define UNIFORM_SPOT_LIGHTS_T			ge_spot_lights_t
#define UNIFORM_DIRECTIONAL_LIGHTS_T	ge_directional_lights_t


#endif


layout(location = VERTEX_POSITION) in vec3 vertexPositions;

uniform mat4 mvp;

out vec3 col;

void main()
{
  gl_Position = mvp * vec4(vertexPositions,1);
}
