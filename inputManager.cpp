#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <cassert>

#include <GLFW/glfw3.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

#include <print>

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
    // mouse TODO make event based also, so we can have on button down and up
    // the movement however is fine I think but I think there is some
    // delta stuff built into SDL?
    int prevMouseX = m_mouseX;
    int prevMouseY = m_mouseY;
    Uint32 mouseState = SDL_GetMouseState(&m_mouseX, &m_mouseY);
    m_leftClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));
    m_rightClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT));
    m_middleClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE));

    m_deltaMouseX = prevMouseX - m_mouseX;
    m_deltaMouseY = prevMouseY - m_mouseY;

    // everything else, mostly keyboard
    std::fill(m_onKeyDown.begin(), m_onKeyDown.end(), false);
    std::fill(m_onKeyUp.begin(), m_onKeyUp.end(), false);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        SDL_Keycode scancode = event.key.keysym.scancode;
        switch (event.type) {
        case SDL_QUIT:
            m_shouldClose = true;
            break;
        case SDL_KEYDOWN:
            if (m_keys[scancode] == false) {
                m_onKeyDown[scancode] = true;
            }
            m_keys[scancode] = true;
            break;
        case SDL_KEYUP:
            if (m_keys[scancode] == true) {
                m_onKeyUp[scancode] = true;
            }
            m_keys[scancode] = false;
            break;
        default:
            break;
        }
    }
}

bool InputManager::isKeyPressed(SDL_Scancode key) { return m_keys[key]; }
bool InputManager::onKeyUp(SDL_Scancode key) { return m_onKeyUp[key]; }
bool InputManager::onKeyDown(SDL_Scancode key) { return m_onKeyDown[key]; }

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
