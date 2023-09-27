#pragma once
#include <eendgine/shader.hpp>
#include <eendgine/texture.hpp>

namespace Eendgine {
    class Sprite {
        public:
            void update(Texture texture);
            void render(Eendgine::Shader *shader);
            float x, y, w, h;
        private:
            unsigned int _VAO;
            float _verticies[32];
            int _indicies[6];
            Texture _texture;
            Eendgine::Shader *_shader;
    };
}
