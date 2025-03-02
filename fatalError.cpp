#include <print>

#include <SDL2/SDL.h>

#include "fatalError.hpp"

namespace Eendgine {
void fatalError(std::string errorMessage) {
    std::print("{}", errorMessage);
    SDL_Quit();
    exit(1);
}

} // namespace Eendgine
