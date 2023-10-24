#include "texture.hpp"
#include "fatalError.hpp"
#include <stb/stb_image.h>
#include <glad/glad.h>

namespace Eendgine {
    Texture loadTexture(std::string filePath){
        int numChannels;
        Texture texture;

        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        unsigned char *imageData = stbi_load(filePath.c_str(), 
                &texture.width, &texture.height, &numChannels, 0);
        if (imageData) {
            glTexImage2D(GL_TEXTURE_2D, 
                    0, GL_RGB, texture.width, texture.height, 
                    0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        } else {
            fatalError("Failed to load image" + filePath);
        }
        stbi_image_free(imageData);
        return texture;
    };
}
