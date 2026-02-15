#pragma once

#include <SDL2/SDL.h>

namespace Eendgine {

class Screen {
    public:
        static void construct(int width, int height);
        static void destruct();
        static Screen& get();

        void bind();
        void render();

    private:
        Screen(int width, int height);
        ~Screen();

        Screen(const Screen&) = delete;
        Screen& operator=(const Screen&) = delete;

        Screen(Screen&& other) = delete;
        Screen& operator=(Screen&& other) = delete;

        inline static Screen* _instance = nullptr;

        int m_width = 0;
        int m_height = 0;
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        unsigned int m_RBO = 0;
        unsigned int m_FB = 0;
        unsigned int m_textureColorBuffer = 0;
        // clang-format off
        // https://stackoverflow.com/questions/2588875/whats-the-best-way-to-draw-a-fullscreen-quad-in-opengl-3-2
        float m_screenTriVerts[12] = {
            -1.0f,  3.0f,  0.0f,  2.0f,
            -1.0f, -1.0f,  0.0f,  0.0f,
             3.0f, -1.0f,  2.0f,  0.0f,
        };
        // clang-format on
};

} // namespace Eendgine
