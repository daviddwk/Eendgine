#include "audio.hpp"

#include <SDL2/SDL_audio.h>
#include <Simple-SDL2-Audio/audio.h>
#include <assert.h>

namespace Eendgine {

Audio::Audio() { initAudio(); }

Audio::~Audio() { endAudio(); }

void Audio::playNoise(std::filesystem::path file, float volume) {
    playSound(file.c_str(), handleVolume(volume));
}

void Audio::playTrack(std::filesystem::path file, float volume) {
    playMusic(file.c_str(), handleVolume(volume));
}

unsigned int Audio::handleVolume(float volume) {
    if (volume < 0.0f) volume = 0.0f;
    if (volume > 100.0f) volume = 100.0f;
    return static_cast<unsigned int>(static_cast<float>(SDL_MIX_MAXVOLUME) * (volume / 100.0f));
}

void Audio::construct() {
    assert(m_instance == nullptr);
    m_instance = new Audio();
}

void Audio::destruct() {
    assert(m_instance != nullptr);
    delete m_instance;
    m_instance = nullptr;
}

Audio& Audio::get() {
    assert(m_instance != nullptr);
    return *m_instance;
}
} // namespace Eendgine
