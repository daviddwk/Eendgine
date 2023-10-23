#pragma once

#include <eendgine/vertex.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/camera3D.hpp>

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
