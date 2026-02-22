#pragma once
#include "texture.hpp"

#include <map>
#include <vector>

namespace Eendgine {
struct Strip {
        Texture texture;
        size_t len;
};

class StripHandler {
    public:
        StripHandler();
        StripHandler(
            std::vector<std::filesystem::path>& texturePaths, std::filesystem::path& metadataPath);

        void setup(
            std::vector<std::filesystem::path>& texturePaths, std::filesystem::path& metadataPath);

        void setStrip(std::string strip);
        void setStripIdx(unsigned int idx);
        void setStripFlip(bool flip);
        void nextStripIdx();

        std::vector<Strip>::size_type getStripLen();
        unsigned int getStripIdx();
        bool getStripFlip();
        Texture getTexture() const;
        std::vector<Texture>::size_type getNumTextures();

    private:
        std::string currentStrip;
        unsigned int currentStripIdx;
        bool flipStrip;
        std::map<std::string, unsigned int> stripMap;
        std::vector<Strip> strips;

    private:
};

} // namespace Eendgine
