#pragma once
#include <ge/entity/component/Component.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/gtx/quaternion.hpp>

namespace ge
{
    struct TransformComponent : public Component
    {
        
        TransformComponent(Entity* e);

        //TODO: add camera stuff
        //TODO: make Transform struct and deprecate modelmat
        void defaultInit();
        void insertToDefaultBatch();

        void destroy();
        void cycle();
        std::string getTypeName();
        
        bool dynamic = false;

        void reCalc();
        
        void setPosition(glm::vec3);
        void setScale(glm::vec3);
        void setRotation(glm::quat);
        
        glm::vec3 getPosition();
        glm::vec3 getScale();
        glm::quat getRotation();
        
        
        
        glm::mat4 getModel();
        
        glm::mat4 getMVP();
        
        glm::vec3* getUPosition();
        glm::vec3* getUScale();
        glm::quat* getURotation();
        
        
        
        glm::mat4* getUModel();
        
        glm::mat4* getUMVP();
        
    private:
        glm::vec3 pos = glm::vec3(0,0,0), scale = glm::vec3(1);
        glm::quat rot = glm::quat();
        
        glm::mat4 model;
        glm::mat4 mvp = glm::mat4(1);
        
        bool shouldUpdate = false;



        static ComponentConstructorRegistry::StartupHook _hook;

    };
}
