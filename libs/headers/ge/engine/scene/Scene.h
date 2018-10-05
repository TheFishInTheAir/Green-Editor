//
// Created by Ethan Breit on 2017-08-15.
//

#pragma once
#include <forward_list>
#include <ge/graphics/types/Texture.h>
#include <ge/graphics/empty_types/MeshData.h>
#include <ge/graphics/types/Shader.h>
#include <memory>
#include <unordered_map>
#include <list>
#include <ge/graphics/types/Image.h>
#include <ge/graphics/empty_types/Scene.h>
#include <ge/graphics/meshes/TriangleMesh.h>
#include <ge/entity/Entity.h>
#include <ge/graphics/types/lights/LightDirectional.h>
#include <ge/graphics/types/lights/LightPoint.h>
#include <ge/graphics/types/lights/LightSpot.h>
#include <ge/graphics/types/lights/AngleShadow.h>
#include <ge/graphics/types/Material.h>


namespace ge
{


	struct Scene
    {

        static Scene* currentScene;

		void loadScene(Empty::Scene);

		void instantiateScene();

		std::string url;

		//Contains:
    	/*
    	 * Textures
    	 * MeshData
    	 * Shaders
    	 * ShaderGroups
		 * ??Images??
		 * 
		 * Sounds (in the future)
		 * 
    	 */

		std::unordered_map<std::string, std::shared_ptr<ge::Texture>>			textures;
		std::unordered_map<std::string, std::shared_ptr<ge::CubeMap>>			cubemaps;

		std::unordered_map<std::string, std::shared_ptr<ge::Empty::MeshData>>	meshes;
		std::unordered_map<std::string, ge::Material>							materials;

		std::unordered_map<std::string, std::shared_ptr<ge::ShaderGroup>>		shaderGroups;
		std::unordered_map<std::string, std::shared_ptr<ge::Shader>>			shaders;
		std::unordered_map<std::string, std::shared_ptr<ge::Audio::AudioClip>>	audioClips;
        
		std::forward_list<Entity*>                                          	uninstantiatedEntities; //Should fix this
        
        Entity* skybox;
		std::string skyboxCubemapName = "";



		std::list<AngleShadow*>			shadows;
	
		std::list<LightDirectional*> 	directionalLights;
		std::list<LightPoint*> 			pointLights;
		std::list<LightSpot*> 			spotLights;

	};
}