#ifndef ge_lights
#define ge_lights

//TODO: Move somewhere else maybe to something like defaults/util/

#pragma include <engine/global_settings.pre>

///Lighting Structs


struct DirLight
{
    vec3 dir;
    float ambient;
    //NOTE: this should include intensity (multiplied alpha I.E. vec3(R*A, G*A, B*A))
	vec3 colour; //All
    int shadowLoc;
};

struct PointLight
{
    vec3 pos;
    float ambient;

    //NOTE: this should include intensity (multiplied alpha I.E. vec3(R*A, G*A, B*A))
	vec3 colour; //All

    float constant;
    float linear;
    float quadratic;
    int shadowLoc;
};


struct SpotLight
{
    vec3 pos;
    vec3 dir;
    float ambient;
    //NOTE: this should include intensity (multiplied alpha I.E. vec3(R*A, G*A, B*A))
	vec3 colour; //All

    float angle;
    float outerAngle;

    int shadowLoc;
};






//
//WARNING: DO NOT LOOK ANY FURTHER, BAD DESIGN DECISIONS LAY BELOW
//


/*


  struct DirectionalLight
  {
  vec3 dir;

  vec3 colour;
  float intensity;
  };


  struct SpotLight
  {
  vec3 pos;

  vec3 dir;

  float angle;

  vec3 colour;
  float intensity;
  };



//Uniforms
#ifdef LIGHTING_UNIFORMS

uniform PointLight UNIFORM_DIRECTIONAL_LIGHTS_IN[MAX_DIRECTIONAL_LIGHTS];
uniform PointLight UNIFORM_POINT_LIGHTS_IN[MAX_POINT_LIGHTS];
//TODO: Implement more

#endif //NO_UNIFORMS




#ifdef VERTEX

//Functions for Vertex Shaders

float calcDirectionalLightDIF(DirectionalLight light, vec3 normal)
{
	vec3 lightDir = normalize(-light.dir);
	return max(dot(normal, lightDir), 0.0);
}

#elif defined FRAGMENT

//Functions for Fragment Shaders

float calcDirectionalLightDIF(DirectionalLight light, vec3 normal)
{
	vec3 lightDir = normalize(-light.dir);
	return max(dot(normalize(normal), lightDir), 0.0);
}

float calcDirectionalLightSPEC(DirectionalLight light, vec3 normal, vec3 cameraPos, vec3 FragPos)
{
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(normalize(light.dir), normalize(normal));

    return max(dot(viewDir, reflectDir), 0.0);
}

#endif
*/

#endif
