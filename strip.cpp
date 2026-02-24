#include "strip.hpp"

#include "fatalError.hpp"

#include <algorithm>
#include <assert.h>
#include <fstream>
#include <json/json.h>

namespace Eendgine {

StripHandler::StripHandler(std::filesystem::path stripPath) : currentStripIdx(0), flipStrip(false) {

    // stripFolder / metadata.json
    // ...         / {strip1}.png
    // ...         / {strip2}.png

    std::filesystem::path basePath = std::filesystem::path("resources") / stripPath;
    std::filesystem::path metadataPath = basePath / "metadata.json";
    std::vector<std::filesystem::path> texturePaths;
    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".png")) {
            texturePaths.push_back(entry.path());
        }
    }

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
}

void StripHandler::setStrip(std::string strip) {
    assert(stripMap.find(strip) != stripMap.end());
    currentStrip = strip;
    setStripIdx(currentStripIdx);
};

void StripHandler::setStripIdx(unsigned int idx) {
    currentStripIdx = idx % strips[stripMap[currentStrip]].len;
};

void StripHandler::setStripFlip(bool flip) { flipStrip = flip; };

void StripHandler::nextStripIdx() {
    currentStripIdx = (currentStripIdx + 1) % strips[stripMap[currentStrip]].len;
};

std::vector<Strip>::size_type StripHandler::getStripLen() {
    return strips[stripMap[currentStrip]].len;
};

unsigned int StripHandler::getStripIdx() { return currentStripIdx; };

bool StripHandler::getStripFlip() { return flipStrip; };

Texture StripHandler::getTexture() const { return strips.at(stripMap.at(currentStrip)).texture; };

std::vector<Texture>::size_type StripHandler::getNumTextures() { return strips.size(); };

} // namespace Eendgine
