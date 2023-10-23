#include <SDL2/SDL.h>
#include <eendgine/fatalError.hpp>
#include <iostream>

namespace Eendgine {
    void fatalError(std::string errorMessage) {
        std::cout << errorMessage << std::endl;
        SDL_Quit();
        exit(1);
    }

}
