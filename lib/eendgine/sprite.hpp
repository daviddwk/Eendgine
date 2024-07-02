#pragma once
#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "camera.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <filesystem>

namespace Eendgine {
    // TODO combine these into one again
    class Sprite {
        public:
            Sprite(std::filesystem::path texturePath);
            Sprite(std::vector<std::filesystem::path> texturePaths);
            std::vector<Texture>::size_type getNumTextures();
            void setTextureIdx(std::vector<Texture>::size_type textureIdx) 
                { _textureIdx = (textureIdx < _textures.size()) ? textureIdx : 0; };
            void setPosition(glm::vec3 position) { _position = position; };
            void setScale(float w, float h) { _size = glm::vec3(w, h, 1.0f); };
            void setRotation(float r) { _rotation = r; };

            unsigned int getTextureIdx() { return _textureIdx; };
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getSize() { return _size; };
            float getRotation() { return _rotation; };
            unsigned int getTexture() { return _textures[_textureIdx].id; };

            void draw(uint shaderId, Camera2D &camera); 
            void draw(uint shaderId, Camera3D &camera); 
        protected:
            void setup(std::vector<std::filesystem::path> &texturePaths);
            glm::vec3 _position;
            glm::vec3 _size;
            float _rotation;
            unsigned int _VAO;
            unsigned int _textureIdx;
            std::vector<Texture> _textures;
    };
}
