#pragma once
#include <eendgine/shader.hpp>

namespace Eendgine {
    class Sprite {
        public:
            void update();
            void render(Eendgine::Shader *shader);
            float x, y, w, h;
        private:
            unsigned int _VAO;
            float _verticies[32];
            int _indicies[6];
            Eendgine::Shader *_shader;
    };
}
