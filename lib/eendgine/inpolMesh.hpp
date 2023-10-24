#pragma once
#include "vertex.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "camera3D.hpp"
#include <string>
#include <vector>

namespace Eendgine {


    class InpolMesh {
        public:
            InpolMesh(std::vector<InpolVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
            void draw(ShaderProgram &shader);
        private:
            void setup();
            
            unsigned int _VAO, _VBO, _EBO;
            std::vector<InpolVertex> _vertices;
            std::vector<unsigned int> _indices;

    };
}
