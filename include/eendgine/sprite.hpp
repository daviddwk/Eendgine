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
            float _verticies[12];
            int _indicies[6];
            Eendgine::ShaderProgram *_shader;
    };
}
