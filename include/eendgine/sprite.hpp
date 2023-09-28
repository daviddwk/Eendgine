#pragma once
#include <eendgine/shader.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/vertex.hpp>

namespace Eendgine {
    class Sprite {
        public:
            void init(float x, float y, float w, float h, Texture texture);
            void render(Eendgine::Shader *shader);
            float x, y, w, h;
        private:
            unsigned int _VAO;
            Texture _texture;
            Eendgine::Shader *_shader;
    };
}
