#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>

#include <array>
#include <cstdint>

namespace Eendgine {
class InputManager {
    public:
        static void construct();
        static void destruct();
        static InputManager& get();

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;

        // static void init();
        void processInput();
        bool isKeyPressed(SDL_Scancode key);
        bool onKeyUp(SDL_Scancode key);
        bool onKeyDown(SDL_Scancode key);

        bool getShouldClose();

        bool isLeftClicked();
        bool onLeftDown();
        bool onLeftUp();
        bool isRightClicked();
        bool onRightDown();
        bool onRightUp();
        bool isMiddleClicked();
        bool onMiddleDown();
        bool onMiddleUp();

        int getMouseX();
        int getMouseY();
        int getDeltaMouseX();
        int getDeltaMouseY();

        void setShouldClose(bool shouldClose);

    private:
        InputManager() = default;
        ~InputManager() = default;

        inline static InputManager* _instance = nullptr;

        bool m_shouldClose = false;

        std::array<bool, SDL_NUM_SCANCODES> m_keys;
        std::array<bool, SDL_NUM_SCANCODES> m_onKeyUp;
        std::array<bool, SDL_NUM_SCANCODES> m_onKeyDown;

        std::array<bool, UINT8_MAX> m_buttons;
        std::array<bool, UINT8_MAX> m_onButtonUp;
        std::array<bool, UINT8_MAX> m_onButtonDown;

        bool m_leftClick = false;
        bool m_rightClick = false;
        bool m_middleClick = false;
        int m_mouseX = 0;
        int m_mouseY = 0;
        int m_deltaMouseX = 0;
        int m_deltaMouseY = 0;
};
} // namespace Eendgine
