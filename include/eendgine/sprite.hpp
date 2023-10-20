#pragma once

#include <eendgine/shader.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/vertex.hpp>
#include <eendgine/camera2D.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace Eendgine {
    class Sprite {
        public:
            Sprite(float x, float y, float w, float h, Texture texture);
            Sprite(float x, float y, float w, float h, std::vector<Texture> textures);
            std::vector<Texture>::size_type getNumTextures();
            void draw(ShaderProgram &shader, Camera2D &camera);
            
            void setTextureIdx(std::vector<Texture>::size_type textureIdx) 
                { _textureIdx = (textureIdx < _textures.size()) ? textureIdx : 0; };
            void setPosition(float x, float y) { _position = glm::vec3(x, y, 0.0f); };
            void setSize(float w, float h) { _size = glm::vec3(w, h, 1.0f); };
            void setRotation(float r) { _rotation = r; };

            unsigned int getTextureIdx() { return _textureIdx; };
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getSize() { return _size; };
            float getRotation() { return _rotation; };


        private:
            void setup(float x, float y, float w, float h, std::vector<Texture> textures);
            glm::vec3 _position;
            glm::vec3 _size;
            float _rotation;
            unsigned int _VAO = 0;
            std::vector<Texture> _textures;
            unsigned int _textureIdx = 0;
    };

    
}
