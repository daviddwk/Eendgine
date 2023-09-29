#pragma once

#include <SDL2/SDL.h>

namespace Eendgine {
    class InputManager {
        public:
            void processInput();
            void init();
            bool leftPress = false;
            bool rightPress = false;
            bool upPress = false;
            bool downPress = false;
            bool spacePress = false; 
        private:
    };
}
