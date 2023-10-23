#pragma once

#include <eendgine/textureCache.hpp>
#include <eendgine/inpolModel.hpp>
#include <eendgine/camera3D.hpp>
#include <eendgine/shader.hpp>

#include <vector>
#include <string>


namespace Eendgine {
    class AnimatedModel {
        public:
            AnimatedModel(std::vector<std::string> modelPaths, TextureCache texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            // scale animation from beginning (0.0f) to end (0.0f) and wraps
            void setAnim(float scale) { _animScale = scale; }
            void setPosition(float x, float y, float z) { 
                    for (auto &m : _inpolModels) { m.setPosition(x, y, z); } };
            void setScale(float x, float y, float z) {
                    for (auto &m : _inpolModels) { m.setScale(x, y, z); } };
            void setTextureIdx(unsigned int idx) {
                    for (auto &m : _inpolModels) { m.setTextureIdx(idx); } };

            // make getters
            float getAnim() { return _animScale; }
        private:
            std::vector<InpolModel> _inpolModels;      
            float _animScale = 0.0f;
    };
}
