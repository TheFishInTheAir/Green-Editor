#pragma once
#include <ge/audio/AudioClip.h>
#include <glm/glm.hpp>
namespace ge
{
    namespace Audio
    {
        struct AudioSource
        {
            //void safeSetClip(AudioClip*); //thread-safe TODO: maybe we should implement this...
            void setClip(AudioClip*);
            AudioClip* getClip();

            glm::vec3 position;
            glm::vec3 velocity;

            bool loop;

            void create();
            bool isCreated();

            void update();

            void play();
            void pause();
            void stop();

            bool isPlaying();

            void destroy();
        private:
            AudioClip* clip = nullptr;

            unsigned int sourceId = 0;
            bool sIsCreated;
        };
    }
}