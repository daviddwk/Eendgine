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
    int prevMouseX = _mouseX;
    int prevMouseY = _mouseY;
    Uint32 mouseState = SDL_GetMouseState(&_mouseX, &_mouseY);
    _leftClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));
    _rightClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT));
    _middleClick = (bool)(mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE));

    _deltaMouseX = prevMouseX - _mouseX;
    _deltaMouseY = prevMouseY - _mouseY;

    _leftPress = keyState[SDL_SCANCODE_LEFT];
    _rightPress = keyState[SDL_SCANCODE_RIGHT];
    _upPress = keyState[SDL_SCANCODE_UP];
    _downPress = keyState[SDL_SCANCODE_DOWN];
    _spacePress = keyState[SDL_SCANCODE_SPACE];

    // unsigned int mouseState = SDL_GetRelativeMouseState(&deltaMouseX, &deltaMouseY);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            _shouldClose = true;
        }
    }
}
bool InputManager::getLeftPress() { return _leftPress; };
bool InputManager::getRightPress() { return _rightPress; };
bool InputManager::getUpPress() { return _upPress; };
bool InputManager::getDownPress() { return _downPress; };
bool InputManager::getSpacePress() { return _spacePress; };
bool InputManager::getShouldClose() { return _shouldClose; };
bool InputManager::getLeftClick() { return _leftClick; };
bool InputManager::getRightClick() { return _rightClick; };
bool InputManager::getMiddleClick() { return _middleClick; };
int InputManager::getMouseX() { return _mouseX; };
int InputManager::getMouseY() { return _mouseY; };
int InputManager::getDeltaMouseX() { return _deltaMouseX; };
int InputManager::getDeltaMouseY() { return _deltaMouseY; };

void InputManager::setShouldClose(bool shouldClose) { _shouldClose = shouldClose; };
} // namespace Eendgine
