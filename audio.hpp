#pragma once

#include <filesystem>

namespace Eendgine {
class Audio {
    public:
        static void construct();
        static void destruct();
        static Audio& get();

        void playNoise(std::filesystem::path file, unsigned int volume);
        void playTrack(std::filesystem::path file, unsigned int volume);

    private:
        Audio();
        ~Audio();

        inline static Audio* m_instance = nullptr;
};
} // namespace Eendgine
