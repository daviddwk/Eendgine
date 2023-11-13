#pragma once
#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "camera.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace Eendgine {
    class Sprite {
        public:
            Sprite(Texture texture);
            Sprite(std::vector<Texture> textures);
            std::vector<Texture>::size_type getNumTextures();
            void draw(ShaderProgram &shader, Camera2D &camera);
            void draw(ShaderProgram &shader, Camera3D &camera);
            
            void setTextureIdx(std::vector<Texture>::size_type textureIdx) 
                { _textureIdx = (textureIdx < _textures.size()) ? textureIdx : 0; };
            void setPosition(float x, float y, float z = 0.0f) { _position = glm::vec3(x, y, z); };
            void setSize(float w, float h) { _size = glm::vec3(w, h, 1.0f); };
            void setRotation(float r) { _rotation = r; };

            unsigned int getTextureIdx() { return _textureIdx; };
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getSize() { return _size; };
            float getRotation() { return _rotation; };


        private:
            void setup(std::vector<Texture> textures);
            glm::vec3 _position;
            glm::vec3 _size;
            float _rotation;
            unsigned int _VAO;
            unsigned int _textureIdx;
            std::vector<Texture> _textures;
    };
}
