#version 330

#pragma include <engine/global_settings.pre>

#ifdef VERTEX

layout(location = VERTEX_POSITION) in vec3 vpos;

uniform mat4 MVP_M;
uniform mat4 MVP_VP;
uniform float GE_TIME;

out vec3 normal;
out vec3 fragpos;

#define DENSITY 5
vec4 calcWave(vec4 wPos)
{
    float t = GE_TIME*1.5;
    float tempY = 0;

    tempY +=sin(wPos.x*DENSITY/8+t/4)/2;


    tempY += sin(wPos.z*DENSITY/8+t/2)/4;
    tempY += cos(wPos.z*DENSITY/8+t/2)/3;

    tempY *= 0.25;


    wPos.y += tempY;
    return wPos;
}



void main()
{
    vec4 tempPos = MVP_M * vec4(vpos, 1);
    vec4 finPos  = calcWave(tempPos);


    vec4 xOff = calcWave(
        vec4(tempPos.x+0.1f, tempPos.yz, 0));
    vec4 zOff = calcWave(
        vec4(tempPos.xy, tempPos.z+0.1f, 0));

    normal = normalize(-vec3(cross(finPos.xyz-xOff.xyz, finPos.xyz-zOff.xyz)));
    //normal = vec3(normal.x, abs(normal.y), normal.z);
    //normal = vec3(cross(vec3(tempPos.x+0.1f, tempPos.yz), vec3(tempPos.xy, tempPos.z+0.1f)));

    fragpos = finPos.xyz;

    gl_Position = MVP_VP * finPos; //send in world space NOTE: using fragpos is a bit of a hack but we save on memory
}

#elif defined FRAGMENT

out vec4 colour;

in vec3  normal;
in vec3  fragpos;

uniform vec3 CAMERA_POS;
uniform samplerCube SKYBOX;


void main()
{
    float fresnelThreshold = 0.7;
    float refractRatio = 1.00 / 1.33; //Waters Refractive index

    vec3 localNormal = normal;// TODO: remove, old test

    vec3 cDir = normalize(fragpos-CAMERA_POS);

    //I don't know how to do fresnel so this is just a guess...
    //float angle = min(max(dot(-cDir, localNormal)*2, 0),1);
    //float angle = clamp(pow(dot(-cDir, localNormal)*2, 2), 0, 1);
    float angle = max(pow(dot(-cDir, localNormal), 2), 0);

    //Refraction
    vec3 refractionVec = refract(cDir, localNormal, refractRatio);
    vec4 refractColour = texture(SKYBOX, refractionVec)*vec4(0.8,1,0.8,1 );

    //Reflection
    vec3 reflectionVec = reflect(cDir, localNormal);
    vec4 reflectColour = texture(SKYBOX, reflectionVec);
    //refractColour = texture(SKYBOX, vec3(reflectionVec.x, -reflectionVec.y, reflectionVec.z));

    //Mix
    colour = mix(reflectColour, refractColour, angle); //TODO: Add fresnel

    //colour *= mix(vec4(1), vec4(0,0.3,0, 1), fragpos.y);

    //colour = refractColour;
    //colour = vec4(normal.x*4, normal.y/2, normal.z*4, 1);// NOTE: TEST
    //colour = vec4((normal+1)/2, 0).xzww;
}


#endif
