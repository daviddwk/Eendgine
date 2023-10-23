#include <iostream>
#include <SDL2/SDL.h>
#include "fatalError.hpp"

namespace Eendgine {
    void fatalError(std::string errorMessage) {
        std::cout << errorMessage << std::endl;
        SDL_Quit();
        exit(1);
    }

}
