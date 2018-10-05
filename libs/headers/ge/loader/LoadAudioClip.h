#pragma once
#include <ge/audio/AudioClip.h>
namespace ge
{
    namespace AudioClipLoader
    {
        Audio::AudioClip* loadAudioClip(std::string url, bool isResource);
    }
}