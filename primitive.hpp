#pragma once

#include <GLES3/gl3.h>

namespace Eendgine {

class Quad {
    public:
        static void construct();
        static void destruct();

        static GLuint getVao();

    private:
        Quad() = default;
        ~Quad() = default;

        inline static GLuint m_VAO = 0;
        inline static GLuint m_VBO = 0;
        inline static GLuint m_EBO = 0;
};
} // namespace Eendgine
