#include <eendgine/texture.hpp>
#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

namespace Eendgine {
    Texture loadTexture(std::string filePath){
        int numChannels;
        Texture texture;

        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        unsigned char *imageData = stbi_load(filePath.c_str(), 
                &texture.width, &texture.height, &numChannels, 0);
        if (imageData) {
            glTexImage2D(GL_TEXTURE_2D, 
                    0, GL_RGB, texture.width, texture.height, 
                    0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load image" << std::endl;
            std::cout << filePath << std::endl;
        }
        stbi_image_free(imageData);
        return texture;
    };
}
