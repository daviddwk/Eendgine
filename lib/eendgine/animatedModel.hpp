#pragma once
#include "textureCache.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include <glm/glm.hpp>
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
            void setRot(float x, float y) {
                    for (auto &m : _inpolModels) { m.setRot(x, y); } };
            void setTextureIdx(unsigned int idx) {
                    for (auto &m : _inpolModels) { m.setTextureIdx(idx); } };
            
            void getAnim(float scale) { _animScale = scale; }
            glm::vec3 getPosition() { return _inpolModels[0].getPosition(); };
            glm::vec3 getScale() { return _inpolModels[0].getScale(); };
            glm::vec2 getRot() { return _inpolModels[0].getRot(); };
            unsigned int getTextureIdx() { return _inpolModels[0].getTextureIdx(); };

            // make getters
            float getAnim() { return _animScale; }
        private:
            std::vector<InpolModel> _inpolModels;      
            float _animScale;
    };
}
