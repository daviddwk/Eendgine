#pragma once
#include <filesystem>
#include <map>
#include <vector>

#include <GLES3/gl3.h>

#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"

namespace Eendgine {
// TODO combine these into one again
class Panel {
    public:
        Panel(std::filesystem::path path);
        ~Panel();
        Panel(const Panel&) = delete;
        Panel& operator=(const Panel&) = delete;
        Panel(Panel&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;

            currentTexture = other.currentTexture;
            textures.swap(other.textures);
        }
        Panel& operator=(Panel&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            VAO = other.VAO;
            VBO = other.VBO;
            EBO = other.EBO;

            currentTexture = other.currentTexture;
            textures.swap(other.textures);
            return *this;
        }
        void eraseBuffers();
        std::vector<Texture>::size_type getNumTextures();
        void setTexture(std::string texture);
        void cropTexture(Point2D upperLeft, Point2D lowerRight);

        std::string getTextureName() { return currentTexture; };
        Texture getTexture() { return textures[currentTexture]; };

        void draw(uint shaderId, Camera2D& camera);

        Point position;
        Scale2D scale;
        float rotation;

    private:
        void setup(std::vector<std::filesystem::path>& texturePaths);
        GLuint VAO, VBO, EBO;
        std::string currentTexture;
        std::map<std::string, Texture> textures;
};
} // namespace Eendgine
