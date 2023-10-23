#pragma once

#include <eendgine/shader.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/vertex.hpp>
#include <eendgine/camera2D.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace Eendgine {
    class 3DSprite {
        public:
            Sprite(Texture texture);
            Sprite(std::vector<Texture> textures);

            std::vector<Texture>::size_type getNumTextures();
            void draw(ShaderProgram &shader, Camera2D &camera);
            
            void setTextureIdx(std::vector<Texture>::size_type textureIdx) 
                { _textureIdx = (textureIdx < _textures.size()) ? textureIdx : 0; };
            void setPosition(float x, float y) { _position = glm::vec3(x, y, 0.0f); };
            void setSize(float w, float h) { _size = glm::vec3(w, h, 1.0f); };

            unsigned int getTextureIdx() { return _textureIdx; };
            glm::vec3 getPosition() { return _position; };
            glm::vec3 getSize() { return _size; };


        private:
            void setup(float x, float y, float w, float h, std::vector<Texture> textures);
            glm::vec3 _position;
            glm::vec3 _size;
            unsigned int _VAO = 0;
            std::vector<Texture> _textures;
            unsigned int _textureIdx = 0;
    };
}
