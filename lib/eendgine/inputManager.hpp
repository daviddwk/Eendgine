#pragma once

namespace Eendgine {
    class InputManager {
        public:
            static void processInput();
            static void init();
            inline static bool leftPress = false;
            inline static bool rightPress = false;
            inline static bool upPress = false;
            inline static bool downPress = false;
            inline static bool spacePress = false; 
            inline static bool shouldClose = false;
            inline static int deltaMouseX = 0;
            inline static int deltaMouseY = 0;
        private:
    };
}
