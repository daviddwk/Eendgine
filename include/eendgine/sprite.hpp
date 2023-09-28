#pragma once
#include <eendgine/shader.hpp>
#include <eendgine/texture.hpp>
#include <eendgine/vertex.hpp>

namespace Eendgine {
    class Sprite {
        public:
            void init(float x, float y, float w, float h, Texture texture);
            void render(Eendgine::Shader *shader);
            
            void setPosition(float x, float y) { _x = x; _y = y; };
            void setRotation(float rotation) { _rotation = rotation; };
            void setScale(float scale) { _scale = scale; };

            float getX() { return _x; };
            float getY() { return _y; };
            float getRotation() { return _rotation; };
            float getScale() { return _scale; };


        private:
            float _x, _y;
            float _w, _h;
            float _rotation, _scale;
            unsigned int _VAO;
            Texture _texture;
            Eendgine::Shader *_shader;
    };
}
