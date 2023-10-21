#pragma once

#include <eendgine/vertex.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/shader.hpp>
#include <eendgine/camera3D.hpp>

#include <string>
#include <vector>

namespace Eendgine {


    class Mesh {
        public:
            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
            void draw(ShaderProgram &shader);
        private:
            void setup();
            
            unsigned int _VAO, _VBO, _EBO;
            std::vector<Vertex> _vertices;
            std::vector<unsigned int> _indices;

    };
}
