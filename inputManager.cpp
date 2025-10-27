#include <cassert>

#include <GLFW/glfw3.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

#include "inputManager.hpp"

namespace Eendgine {

void InputManager::construct() {
    assert(_instance == nullptr);
    _instance = new InputManager;
}

void InputManager::destruct() {
    assert(_instance != nullptr);
    delete _instance;
    _instance = nullptr;
}

InputManager& InputManager::get() {
    assert(_instance != nullptr);
    return *_instance;
}

void InputManager::processInput() {
    // const unsigned char *keyState = SDL_GetKeyboardState(nullptr);

    const unsigned char* keyState = SDL_GetKeyboardState(nullptr);
    int prevMouseX = m_mouseX;
    int prevMouseY = m_mouseY;
    Uint32 mouseState = SDL_GetMouseState(&m_mouseX, &m_mouseY);
    m_leftClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));
    m_rightClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT));
    m_middleClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE));

    m_deltaMouseX = prevMouseX - m_mouseX;
    m_deltaMouseY = prevMouseY - m_mouseY;

    m_leftPress = keyState[SDL_SCANCODE_LEFT];
    m_rightPress = keyState[SDL_SCANCODE_RIGHT];
    m_upPress = keyState[SDL_SCANCODE_UP];
    m_downPress = keyState[SDL_SCANCODE_DOWN];
    m_spacePress = keyState[SDL_SCANCODE_SPACE];
    m_escapePress = keyState[SDL_SCANCODE_ESCAPE];

    // unsigned int mouseState = SDL_GetRelativeMouseState(&deltaMouseX, &deltaMouseY);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            m_shouldClose = true;
        }
    }
}
bool InputManager::getLeftPress() { return m_leftPress; };
bool InputManager::getRightPress() { return m_rightPress; };
bool InputManager::getUpPress() { return m_upPress; };
bool InputManager::getDownPress() { return m_downPress; };
bool InputManager::getSpacePress() { return m_spacePress; };
bool InputManager::getEscapePress() { return m_escapePress; }
bool InputManager::getShouldClose() { return m_shouldClose; };
bool InputManager::getLeftClick() { return m_leftClick; };
bool InputManager::getRightClick() { return m_rightClick; };
bool InputManager::getMiddleClick() { return m_middleClick; };
int InputManager::getMouseX() { return m_mouseX; };
int InputManager::getMouseY() { return m_mouseY; };
int InputManager::getDeltaMouseX() { return m_deltaMouseX; };
int InputManager::getDeltaMouseY() { return m_deltaMouseY; };

void InputManager::setShouldClose(bool shouldClose) { m_shouldClose = shouldClose; };
} // namespace Eendgine
