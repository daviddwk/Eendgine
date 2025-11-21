#include "fatalError.hpp"
#include "texture.hpp"
#include <GLES3/gl3.h>
#include <stb/stb_image.h>

namespace Eendgine {
Texture loadTexture(std::filesystem::path filePath) {
    int numChannels;
    Texture texture;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char* imageData =
        stbi_load(filePath.c_str(), &texture.width, &texture.height, &numChannels, 3);
    if (imageData) {
        if (numChannels >= 3) {
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGB,
                texture.width,
                texture.height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                imageData);
        } else {
            fatalError("Image " + std::to_string(numChannels) + " channels: " + filePath.string());
        }
    } else {
        fatalError("Failed to load image: " + filePath.string());
    }
    stbi_image_free(imageData);
    return texture;
};
} // namespace Eendgine
