#pragma once
#include <ge/entity/component/Component.h>
#include <ge/entity/component/components/TransformComponent.h>
#include <ge/entity/component/ComponentConstructorRegistry.h>
#include <ge/audio/AudioSource.h>
#include <vector>

namespace ge
{
    struct AudioSourceComponent : public Component
    {
        AudioSourceComponent(Entity*);
        AudioSourceComponent(Entity*, Audio::AudioSource*);

        void defaultInit();
        void insertToDefaultBatch();
        
        void play();
        void pause();
        void stop();

        void cycle();
        void destroy();
        std::string getTypeName();
        
        Audio::AudioSource* source;
    private:

        void init();
    
        bool queuePlay = false;
        bool queuePause = false;
        bool queueStop = false;

		std::string currentAudioSource			= "NONE";
		std::string currentAudioSourceCACHED	= "NONE";

        TransformComponent* transformComponent = nullptr;
        static ComponentConstructorRegistry::StartupHook _hook;

    };
}
