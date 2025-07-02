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

        bool _leftPress = false;
        bool _rightPress = false;
        bool _upPress = false;
        bool _downPress = false;
        bool _spacePress = false;
        bool _shouldClose = false;
        bool _leftClick = false;
        bool _rightClick = false;
        bool _middleClick = false;
        int _mouseX = 0;
        int _mouseY = 0;
        int _deltaMouseX = 0;
        int _deltaMouseY = 0;
};
} // namespace Eendgine
