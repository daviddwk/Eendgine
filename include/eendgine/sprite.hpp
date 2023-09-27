#pragma once
#include <eendgine/shader.hpp>

namespace Eendgine {
    class Sprite {
        public:
            void update();
            void render(Eendgine::ShaderProgram *shader);
            float x, y, w, h;
        private:
            unsigned int _VAO;
            Eendgine::ShaderProgram *_shader;
    };
}
