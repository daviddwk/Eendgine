#pragma once

#include <eendgine/textureCache.hpp>
#include <eendgine/lerpModel.hpp>
#include <eendgine/camera3D.hpp>
#include <eendgine/shader.hpp>

#include <vector>
#include <string>


namespace Eendgine {
    class AnimatedModel {
        public:
            AnimatedModel(std::vector<std::string> modelPaths, TextureCache texCache);
            void draw(ShaderProgram &shader, Camera3D &camera);

            // anim time wraps from 0 to 1
            void setAnimTime(float at) { _animTime = at; }
            void setPosition(float x, float y, float z) { 
                    for (auto &m : _lerpModels) { m.setPosition(x, y, z); } };
            void setScale(float x, float y, float z) {
                    for (auto &m : _lerpModels) { m.setScale(x, y, z); } };
            void setTextureIdx(unsigned int idx) {
                    for (auto &m : _lerpModels) { m.setTextureIdx(idx); } };

            // make getters
            float getAnimTime() { return _animTime; }
        private:
            std::vector<LerpModel> _lerpModels;      
            float _animTime = 0.0f;
    };
}
