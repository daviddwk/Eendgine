#pragma once

#include <eendgine/shader.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/vertex.hpp>
#include <eendgine/camera2D.hpp>

#include <vector>

namespace Eendgine {
    class Sprite {
        public:
            void init(float x, float y, float w, float h, Texture textures);
            void init(float x, float y, float w, float h, std::vector<Texture> textures);
            void setTexture(std::vector<Texture>::size_type textureIndex);
            std::vector<Texture>::size_type getNumTextures();
            void render(Eendgine::ShaderProgram *shader, Eendgine::Camera2D *camera);
            
            float x = 0, y = 0;
            float w = 1, h = 1;
            float rotation = 0, scale = 1;
        private:
            unsigned int _VAO = 0;
            std::vector<Texture> _textures;
            Texture *_currentTexture = nullptr;
            Eendgine::ShaderProgram *_shader = nullptr;
    };

    
}
