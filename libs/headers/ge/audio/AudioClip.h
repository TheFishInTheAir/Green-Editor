#pragma once

#include <string>

namespace ge
{
    namespace Audio
    {
        struct AudioClip
        {
            std::string url;

            short* data;
            int sampleRate;
            int samples;
            int channels;

            void upload();
            bool isReady();

            unsigned int getALId();

        private:
            bool bufferExists = false;
            unsigned int bufferId = 0;
        };
    }
}