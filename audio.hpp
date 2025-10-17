#pragma once

#include <SDL2/SDL_audio.h>
#include <filesystem>

namespace Eendgine {
class Audio {
    public:
        static void construct();
        static void destruct();
        static Audio& get();

        void playNoise(std::filesystem::path file, float volume);
        void playTrack(std::filesystem::path file, float volume);

    private:
        Audio();
        ~Audio();

        unsigned int handleVolume(float volume);

        inline static Audio* m_instance = nullptr;
};
} // namespace Eendgine
