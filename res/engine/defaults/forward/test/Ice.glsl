#version 330

#pragma include <engine/global_settings.pre>

#ifdef VERTEX

layout(location = VERTEX_POSITION) in vec3 vpos;
layout(location = NORMAL_POSITION) in vec3 normals;

out vec3 tNormals;
out vec3 fragpos;

uniform mat4 MVP_M;
uniform mat4 MVP_VP;

void main()
{
    gl_Position = MVP_M_VP * vec4(vpos, 1);
    fragpos = vec3(MVP_M * vec4(vpos, 1.0));
	tNormals = normalize(transpose(inverse(mat3(MVP_M))) * normals);
}

#elif defined FRAGMENT

out vec4 colour;

in vec3 tNormals;
in vec3 fragpos;

uniform vec3 CAMERA_POS;

uniform samplerCube SKYBOX;


void main()
{
    //colour = vec4(1,0,1,1);
    float ratio = 1.00 / (1.309 * 1);

    vec3 I = normalize(fragpos - CAMERA_POS);

    vec3 R = refract(I, normalize(tNormals), ratio);

    colour = vec4(texture(SKYBOX, R).rgb, 1.0);
}


#endif
