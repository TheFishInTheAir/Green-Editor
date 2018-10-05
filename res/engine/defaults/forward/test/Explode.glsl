#version 330

#pragma include <engine/global_settings.pre>

#ifdef VERTEX

layout(location = VERTEX_POSITION) in vec3 vpos;
layout(location = NORMAL_POSITION) in vec3 normals;

out VS_OUT {
    vec3 normal;
    vec3 tNormals;
    vec3 fragpos;

} vs_out;

uniform mat4 MVP_M;
uniform mat4 MVP_V;
uniform mat4 MVP_P;


void main()
{
    gl_Position = MVP_M_V_P * vec4(vpos, 1);
    vs_out.fragpos = vec3(MVP_M * vec4(vpos, 1.0));


    mat3 normalMatrix = mat3(transpose(inverse(MVP_M)));
    vs_out.normal = normalize(vec3(MVP_P * vec4(normalMatrix * normals, 1.0)));

	vs_out.tNormals = normalize(normalMatrix * normals);
}

#elif defined GEOMETRY

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 tNormals;
out vec3 fragpos;

uniform float GE_TIME;

in VS_OUT {
    vec3 normal;
    vec3 tNormals;
    vec3 fragpos;
} gs_in[];

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 1.0;
    vec3 direction = normal * ((sin(GE_TIME) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction.xy, 0, 0.0);
}

void drawIndex(int i)
{
    gl_Position = explode(gl_in[i].gl_Position, mix(GetNormal(),gs_in[i].normal, 0.1));
    tNormals = gs_in[i].tNormals;
    fragpos  = vec3(explode(vec4(gs_in[i].fragpos,0), mix(GetNormal(),gs_in[i].normal, 0.1)));
    //fragpos = gs_in[i].fragpos;
    EmitVertex();
}

void main()
{
    drawIndex(0); // first vertex normal
    drawIndex(1); // second vertex normal
    drawIndex(2); // third vertex normal
    EndPrimitive();
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
