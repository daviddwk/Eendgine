#include "fatalError.hpp"
#include <SDL2/SDL.h>
#include <iostream>

namespace Eendgine {
void fatalError(std::string errorMessage) {
    std::cout << errorMessage << std::endl;
    SDL_Quit();
    exit(1);
}

} // namespace Eendgine
