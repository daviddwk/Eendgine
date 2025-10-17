#include "audio.hpp"

#include <Simple-SDL2-Audio/audio.h>
#include <assert.h>

namespace Eendgine {

Audio::Audio() { initAudio(); }

Audio::~Audio() { endAudio(); }

void Audio::playNoise(std::filesystem::path file, unsigned int volume) {
    playSound(file.c_str(), volume);
}

void Audio::playTrack(std::filesystem::path file, unsigned int volume) {
    playMusic(file.c_str(), volume);
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
