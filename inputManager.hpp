#pragma once

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

        bool getLeftPress();
        bool getRightPress();
        bool getUpPress();
        bool getDownPress();
        bool getSpacePress();
        bool getEscapePress();
        bool getShouldClose();
        bool getLeftClick();
        bool getRightClick();
        bool getMiddleClick();
        int getMouseX();
        int getMouseY();
        int getDeltaMouseX();
        int getDeltaMouseY();

        void setShouldClose(bool shouldClose);

    private:
        InputManager() = default;
        ~InputManager() = default;

        inline static InputManager* _instance = nullptr;

        bool m_leftPress = false;
        bool m_rightPress = false;
        bool m_upPress = false;
        bool m_downPress = false;
        bool m_spacePress = false;
        bool m_escapePress = false;
        bool m_shouldClose = false;
        bool m_leftClick = false;
        bool m_rightClick = false;
        bool m_middleClick = false;
        int m_mouseX = 0;
        int m_mouseY = 0;
        int m_deltaMouseX = 0;
        int m_deltaMouseY = 0;
};
} // namespace Eendgine
