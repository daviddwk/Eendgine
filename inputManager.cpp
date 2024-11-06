#include "inputManager.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>

namespace Eendgine {

void InputManager::init() {}

void InputManager::processInput() {
    // const unsigned char *keyState = SDL_GetKeyboardState(nullptr);

    const unsigned char* keyState = SDL_GetKeyboardState(nullptr);

    leftPress = keyState[SDL_SCANCODE_LEFT];
    rightPress = keyState[SDL_SCANCODE_RIGHT];
    upPress = keyState[SDL_SCANCODE_UP];
    downPress = keyState[SDL_SCANCODE_DOWN];
    spacePress = keyState[SDL_SCANCODE_SPACE];

    // unsigned int mouseState = SDL_GetRelativeMouseState(&deltaMouseX, &deltaMouseY);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            shouldClose = true;
        }
    }
}

} // namespace Eendgine
