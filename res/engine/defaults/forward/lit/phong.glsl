#version 330

#pragma include <engine/global_settings.pre>
#pragma include <engine/shader/lighting/lights.glsl>

#ifdef VERTEX

layout(location = VERTEX_POSITION) in vec3 vpos;
layout(location = UV_POSITION)     in vec2 texcoord;
layout(location = NORMAL_POSITION) in vec3 normals;

uniform mat4 MVP_M;
uniform mat4 MVP_VP;

out vec3 tNormals;
out vec2 tTexcoord;
out vec4 tFragcoord;

out vec4 lightFragCoords[A_SHADOW_MAX];

uniform mat4 A_SHADOW_SPACE_IN[A_SHADOW_MAX];
uniform int A_SHADOW_NUM;
void main()
{
    gl_Position = MVP_M_VP * vec4(vpos, 1);


    mat3 normalMatrix = transpose(inverse(mat3(MVP_M))); //TODO: calculate normal matrix on CPU

    tFragcoord = MVP_M * vec4(vpos, 1);
	tNormals = normalize(normalMatrix * normals);
    tTexcoord = texcoord;

    for(int i = 0; i < A_SHADOW_NUM; i++)
    {
        lightFragCoords[i] = A_SHADOW_SPACE_IN[i] * MVP_M * vec4(vpos, 1); //TODO: clamp here
    }
}

#elif defined FRAGMENT

out vec4 colour;

in vec3 tNormals;
in vec2 tTexcoord;
in vec4 tFragcoord; //World space

in vec4 lightFragCoords[A_SHADOW_MAX];



uniform vec3 CAMERA_POS;

uniform sampler2D ALBEDO_REF;
uniform sampler2D SPECULAR_REF;
//TODO: add normal maps

uniform DirLight LIGHT_DIR_IN[LIGHT_DIR_MAX];
uniform int LIGHT_DIR_NUM;

uniform PointLight LIGHT_POINT_IN[LIGHT_POINT_MAX];
uniform int LIGHT_POINT_NUM;

uniform SpotLight LIGHT_SPOT_IN[LIGHT_SPOT_MAX];
uniform int LIGHT_SPOT_NUM;

uniform sampler2D A_SHADOW_MAP_IN[A_SHADOW_MAX];
uniform int A_SHADOW_NUM;
//Phong Lighting


float computeShadow(int i, vec3 lightDir)
{
    // perform perspective divide
    vec3 projCoords = lightFragCoords[i].xyz / lightFragCoords[i].w;

    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // get closest depth value from light’s perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(A_SHADOW_MAP_IN[i], clamp(projCoords.xy, vec2(0), vec2(1))).r;

    // get depth of current fragment from light’s perspective
    float currentDepth = projCoords.z;

    // check whether current frag pos is in shadow
	//float shadow = 0;
	//if (texture(shadowMap, (ShadowCoord.xy / ShadowCoord.w)).z  <  (ShadowCoord.z - bias) / ShadowCoord.w)
	float bias = max(0.05 * (1.0 - dot(tNormals, lightDir)), 0.005);
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    return shadow;
}

vec3 computeDirectionalLight(DirLight l)
{
    vec4 lCol = vec4(l.colour, 1); 
    vec4 colour = vec4(0);

    vec3 normalLightDir = normalize(l.dir);

    //AMBIENT
    vec4 ambient = l.ambient * lCol;

    //Diffuse
    vec4 diff =
        max(dot(-normalLightDir, tNormals),0) *
        lCol;


    //Specular
    float specAmnt = dot(reflect(normalLightDir, tNormals),
                     normalize(CAMERA_POS-vec3(tFragcoord)));
    vec4 spec =
        pow(max(specAmnt,0),32) * //32 is an arbitrary default, I might change it to 64 or something
        lCol *
        texture(SPECULAR_REF, tTexcoord);

    colour += texture(ALBEDO_REF, tTexcoord) * (ambient + diff + spec);

    return vec3(colour);
}

vec3 computePointLight(PointLight l)
{
	vec4 lCol = vec4(l.colour, 1);
	vec4 colour = vec4(0);

    vec3 normalLightDir = normalize(tFragcoord.xyz - l.pos);

    //Attenuation
    float distance    = length(tFragcoord.xyz - l.pos );
    float attenuation = 1.0 / (l.constant + l.linear * distance +
                l.quadratic * (distance * distance));

    //AMBIENT
    vec4 ambient = l.ambient * lCol * attenuation;

    //Diffuse
    vec4 diff =
        max(dot(-normalLightDir, tNormals),0) *
        lCol * attenuation;


    //Specular
    float specAmnt = dot(reflect(normalLightDir, tNormals),
                     normalize(CAMERA_POS-vec3(tFragcoord)));
    vec4 spec =
        pow(max(specAmnt,0),32) * //32 is an arbitrary default, I might change it to 64 or something
        lCol *
        texture(SPECULAR_REF, tTexcoord) * attenuation;

    colour += texture(ALBEDO_REF, tTexcoord) * (ambient + diff + spec);

    return vec3(colour);
}

vec3 computeSpotLight(SpotLight l)
{
	vec4 lCol = vec4(l.colour, 1);
	vec4 colour = vec4(0);

    vec3 normalLightDir = normalize(tFragcoord.xyz - l.pos);

    float theta = dot(-normalLightDir, normalize(-l.dir));
    float epsilon = l.angle - l.outerAngle;
    float intensity = clamp((theta - l.outerAngle) / epsilon, 0.0, 1.0);

    //AMBIENT
    vec4 ambient = l.ambient * lCol * intensity;


    //Diffuse
    vec4 diff =
        max(dot(-normalLightDir, tNormals),0) *
        lCol * intensity;

    //Specular
    float specAmnt = dot(reflect(normalLightDir, tNormals),
                        normalize(CAMERA_POS-vec3(tFragcoord)));
    vec4 spec =
        pow(max(specAmnt,0),32) * //32 is an arbitrary default, I might change it to 64 or something
        lCol *
        texture(SPECULAR_REF, tTexcoord)  * intensity;

    float shadowAmnt = 0.0f;
    if(l.shadowLoc!=-1)
    {
        //colour = texture(A_SHADOW_MAP_IN[l.shadowLoc], tTexcoord);

        shadowAmnt = computeShadow(l.shadowLoc, normalLightDir);
    }

    colour += texture(ALBEDO_REF, tTexcoord) * (ambient + (1.0 - shadowAmnt) * (diff + spec));
	//colour = vec4(1.0 - shadowAmnt);
    return vec3(colour);
}

vec3 computeLights()
{
    vec3 currentColour = vec3(0);

    for(int i = 0; i < LIGHT_DIR_NUM; i++)
        currentColour += computeDirectionalLight(LIGHT_DIR_IN[i]);
    for(int i = 0; i < LIGHT_POINT_NUM; i++)
        currentColour += computePointLight(LIGHT_POINT_IN[i]);
    for(int i = 0; i < LIGHT_SPOT_NUM; i++)
        currentColour += computeSpotLight(LIGHT_SPOT_IN[i]);



    return currentColour;
}

void main()
{
    //vec3 colour = vec3(0);

    //AMBIENT
    //colour += vec3(0.1);

    //Lighting
    colour = vec4(computeLights(), 1);
    //colour = vec4(texture(ALBEDO_REF, tTexcoord));
}


#endif
