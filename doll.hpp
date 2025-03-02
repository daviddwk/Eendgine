#pragma once

#include <filesystem>
#include <map>
#include <print>
#include <string>
#include <vector>

#include <GLES3/gl3.h>

#include "camera.hpp"
#include "texture.hpp"
#include "types.hpp"
#include "vertex.hpp"

namespace Eendgine {
class Doll {
    public:
        Doll(std::filesystem::path dollPath);
        ~Doll();

        Doll(const Doll&) = delete;
        Doll& operator=(const Doll&) = delete;
        Doll(Doll&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            animation = other.animation;
            VAOs.swap(other.VAOs);
            VBOs.swap(other.VBOs);
            EBOs.swap(other.EBOs);
            numIndices = other.numIndices;

            animScale = other.animScale;
            currentTextureIdx = other.currentTextureIdx;
            textures.swap(other.textures);
        }
        Doll& operator=(Doll&& other) {
            position = other.position;
            scale = other.scale;
            rotation = other.rotation;

            animation = other.animation;
            VAOs.swap(other.VAOs);
            VBOs.swap(other.VBOs);
            EBOs.swap(other.EBOs);
            numIndices = other.numIndices;

            animScale = other.animScale;
            currentTextureIdx = other.currentTextureIdx;
            textures.swap(other.textures);
            return *this;
        }

        void eraseBuffers();

        void setAnimation(std::string animationName);
        void setAnimScale(float scale) { animScale = scale - (int)scale; };
        void setTextureIdx(unsigned int idx) {
            currentTextureIdx = (idx < textures.size() ? idx : 0);
        };

        std::string getAnimation() { return animation; };
        float getAnimScale() { return animScale; };
        unsigned int getTextureIdx() { return currentTextureIdx; };
        Texture getTexture() { return textures[currentTextureIdx]; };

        void draw(uint shaderId, Camera3D& camera);

        Point position;
        Scale scale;
        Rotation rotation;

    private:
        std::string animation;
        std::map<std::string, std::vector<GLuint>> VAOs, VBOs, EBOs;
        unsigned int numIndices;

        float animScale;
        unsigned int currentTextureIdx;
        std::vector<Texture> textures;
};
} // namespace Eendgine
