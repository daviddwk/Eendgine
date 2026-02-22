#pragma once

#include "camera.hpp"
#include "fatalError.hpp"
#include "texture.hpp"
#include "textureCache.hpp"
#include "types.hpp"

#include <filesystem>
#include <fstream>
#include <json/json.h>
#include <map>
#include <vector>

namespace Eendgine {
class StripHandler {
    public:
        StripHandler() : flipStrip(false) {};
        StripHandler(
            std::vector<std::filesystem::path> texturePaths, std::filesystem::path metadataPath)
            : flipStrip(false) {

            // sorting them alphabetically, becasue the order they're iterated on
            // is not specified
            std::sort(texturePaths.begin(), texturePaths.end(), [](auto a, auto b) {
                return a.string() < b.string();
            });
            for (const auto& t : texturePaths) {
                if (t.has_stem() == false) {
                    fatalError("texture: " + t.string() + "has no stem");
                }
                stripMap[t.stem()] = strips.size();
                strips.push_back((Strip){TextureCache::getTexture(t), 1}); // default to 1
            }
            assert(stripMap.size() > 0);

            auto [stripName, stripIdx] = *stripMap.begin();
            currentStrip = stripName;

            Json::Value rootJson;
            std::ifstream metadata(metadataPath);
            if (metadata.is_open()) {
                try {
                    metadata >> rootJson;
                } catch (...) {
                    fatalError("improper json: " + metadataPath.string());
                }
                for (const auto& t : texturePaths) {
                    if (rootJson[t.stem()].isUInt()) {
                        strips[stripMap[t.stem()]].len = rootJson[t.stem()].asUInt();
                    }
                }
            }
        };

        void setStrip(std::string strip) {
            assert(stripMap.find(strip) != stripMap.end());
            currentStrip = strip;
            currentStripIdx = 0;
        };

        void setStripIdx(unsigned int idx) {
            currentStripIdx = idx % strips[stripMap[currentStrip]].len;
        };

        void setStripFlip(bool flip) { flipStrip = flip; };

        void nextStripIdx() {
            currentStripIdx = (currentStripIdx + 1) % strips[stripMap[currentStrip]].len;
        };

        std::vector<Strip>::size_type getStripLen() { return strips[stripMap[currentStrip]].len; };

        unsigned int getStripIdx() { return currentStripIdx; };

        bool getStripFlip() { return flipStrip; };

        Texture getTexture() const { return strips.at(stripMap.at(currentStrip)).texture; };

        std::vector<Texture>::size_type getNumTextures() { return strips.size(); };

    private:
        std::string currentStrip;
        unsigned int currentStripIdx;
        bool flipStrip;
        std::map<std::string, unsigned int> stripMap;
        std::vector<Strip> strips;

    private:
};

class Board {
    public:
        Board(std::filesystem::path path);
        ~Board() = default;

        Board(const Board& other) = delete;
        Board& operator=(const Board& other) = delete;

        Board(Board&& other) noexcept = default;
        Board& operator=(Board&& other) noexcept = default;

        void setStrip(std::string strip);
        void setStripIdx(unsigned int idx);
        void nextStripIdx();
        void setStripFlip(bool flip);

        void setPosition(Point position);
        void setScale(Scale2D scale);
        void setRotation(float r);

        std::vector<Strip>::size_type getStripLen();
        unsigned int getStripIdx();

        Point getPosition();
        Scale getSize();
        float getRotation();

        Texture getTexture() const;

        std::vector<Texture>::size_type getNumTextures();
        void draw(GLuint shaderId, Camera3D& camera);

    private:
        void setup(
            std::vector<std::filesystem::path>& texturePaths, std::filesystem::path& metadataPath);

        Point m_position;
        Scale m_size;
        float m_rotation;

        StripHandler m_stripHandler;
};
} // namespace Eendgine
