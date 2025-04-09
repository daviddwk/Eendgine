#pragma once

namespace Eendgine {
class InputManager {
    public:
        static void init();
        static void processInput();

        static bool getLeftPress();
        static bool getRightPress();
        static bool getUpPress();
        static bool getDownPress();
        static bool getSpacePress();
        static bool getShouldClose();
        static bool getLeftClick();
        static bool getRightClick();
        static bool getMiddleClick();
        static int getMouseX();
        static int getMouseY();
        static int getDeltaMouseX();
        static int getDeltaMouseY();

        static void setShouldClose(bool shouldClose);

    private:
        inline static bool _leftPress = false;
        inline static bool _rightPress = false;
        inline static bool _upPress = false;
        inline static bool _downPress = false;
        inline static bool _spacePress = false;
        inline static bool _shouldClose = false;
        inline static bool _leftClick = false;
        inline static bool _rightClick = false;
        inline static bool _middleClick = false;
        inline static int _mouseX = 0;
        inline static int _mouseY = 0;
        inline static int _deltaMouseX = 0;
        inline static int _deltaMouseY = 0;
};
} // namespace Eendgine
