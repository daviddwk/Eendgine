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

    // mouse movement
    {
        int prevMouseX = m_mouseX;
        int prevMouseY = m_mouseY;
        Uint32 mouseState = SDL_GetMouseState(&m_mouseX, &m_mouseY);
        m_deltaMouseX = prevMouseX - m_mouseX;
        m_deltaMouseY = prevMouseY - m_mouseY;
    }

    // buttons
    {
        std::fill(m_onKeyDown.begin(), m_onKeyDown.end(), false);
        std::fill(m_onKeyUp.begin(), m_onKeyUp.end(), false);
        std::fill(m_onButtonDown.begin(), m_onButtonDown.end(), false);
        std::fill(m_onButtonUp.begin(), m_onButtonUp.end(), false);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            SDL_Keycode keycode = event.key.keysym.scancode;
            Uint8 mouseCode = event.button.button;
            switch (event.type) {
            case SDL_QUIT:
                m_shouldClose = true;
                break;
            case SDL_KEYDOWN:
                if (m_keys[keycode] == false) {
                    m_onKeyDown[keycode] = true;
                }
                m_keys[keycode] = true;
                break;
            case SDL_KEYUP:
                if (m_keys[keycode] == true) {
                    m_onKeyUp[keycode] = true;
                }
                m_keys[keycode] = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (m_buttons[mouseCode] == false) {
                    m_onButtonDown[mouseCode] = true;
                }
                m_buttons[mouseCode] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (m_buttons[mouseCode] == true) {
                    m_onButtonUp[mouseCode] = true;
                }
                m_buttons[mouseCode] = false;
                break;
            default:
                break;
            }
        }
    }
}

bool InputManager::isKeyPressed(SDL_Scancode key) { return m_keys[key]; }
bool InputManager::onKeyUp(SDL_Scancode key) { return m_onKeyUp[key]; }
bool InputManager::onKeyDown(SDL_Scancode key) { return m_onKeyDown[key]; }

bool InputManager::getShouldClose() { return m_shouldClose; };

bool InputManager::isLeftClicked() { return m_buttons[SDL_BUTTON_LEFT]; };
bool InputManager::onLeftUp() { return m_onButtonUp[SDL_BUTTON_LEFT]; };
bool InputManager::onLeftDown() { return m_onButtonDown[SDL_BUTTON_LEFT]; };

bool InputManager::isRightClicked() { return m_buttons[SDL_BUTTON_RIGHT]; };
bool InputManager::onRightUp() { return m_onButtonUp[SDL_BUTTON_RIGHT]; };
bool InputManager::onRightDown() { return m_onButtonDown[SDL_BUTTON_RIGHT]; };

bool InputManager::isMiddleClicked() { return m_buttons[SDL_BUTTON_MIDDLE]; };
bool InputManager::onMiddleUp() { return m_onButtonUp[SDL_BUTTON_MIDDLE]; };
bool InputManager::onMiddleDown() { return m_onButtonDown[SDL_BUTTON_MIDDLE]; };

int InputManager::getMouseX() { return m_mouseX; };
int InputManager::getMouseY() { return m_mouseY; };
int InputManager::getDeltaMouseX() { return m_deltaMouseX; };
int InputManager::getDeltaMouseY() { return m_deltaMouseY; };

void InputManager::setShouldClose(bool shouldClose) { m_shouldClose = shouldClose; };
} // namespace Eendgine
