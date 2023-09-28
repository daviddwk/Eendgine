#pragma once
#include <eendgine/shader.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/vertex.hpp>
#include <eendgine/camera2D.hpp>

namespace Eendgine {
    class Sprite {
        public:
            void init(float x, float y, float w, float h, Texture texture);
            void render(Eendgine::ShaderProgram *shader, Eendgine::Camera2D *camera);
            
            void setPosition(float x, float y) { _x = x; _y = y; }
            void setRotation(float rotation) { _rotation = rotation; }
            void setScale(float scale) { _scale = scale; }

            float getX() { return _x; }
            float getY() { return _y; }
            float getRotation() { return _rotation; }
            float getScale() { return _scale; }

        private:
            float _x = 0, _y = 0;
            float _w = 1, _h = 1;
            float _rotation = 0, _scale = 1;
            unsigned int _VAO = 0;
            Texture _texture;
            Eendgine::ShaderProgram *_shader;
    };

    
}
