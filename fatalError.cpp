#include "fatalError.hpp"
#include <SDL2/SDL.h>
#include <print>

namespace Eendgine {
void fatalError(std::string errorMessage) {
    std::print("{}", errorMessage);
    SDL_Quit();
    exit(1);
}

} // namespace Eendgine
