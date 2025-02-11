#include "fatalError.hpp"
#include "text.hpp"
#include <filesystem>
#include <fstream>
#include <json/json.h>
#include <stb/stb_image.h>

std::array possibleChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\'', '"', '.', ',', '?', '!', ':'};

namespace Eendgine {
Text::Text(std::filesystem::path fontName, std::string text, Point position, float scale)
    : _fontPath(std::filesystem::path("resources") / "fonts" / fontName), _position(position),
      _scale(scale) {

    Json::Value root;
    std::filesystem::path metadataPath = _fontPath / "metadata.json";
    std::ifstream metadata(metadataPath);
    if (!metadata.is_open()) {
        fatalError("could not open: " + metadataPath.string());
    }
    try {
        metadata >> root;
    } catch (...) {
        fatalError("improper json: " + metadataPath.string());
    }

    // find the width of the png

    for (const char ch : possibleChars) {
        std::string chString = std::to_string(ch);
        if (root[chString]["first"].isNumeric() && root[chString]["last"].isNumeric()) {
            unsigned int firstColumn = root[chString]["first"].asUInt();
            unsigned int secondColumn = root[chString]["last"].asUInt();
            if (firstColumn < secondColumn) {
                // TODO bail to debault
            }
            _charColumns[ch][0] = firstColumn;
            _charColumns[ch][1] = secondColumn;
            // TODO if column > num columns in image

        } else {
            // have default texture drawn if misisng from hash map
        }
    }
}

Text::~Text() {
    for (const PanelId& id : _panelIds) {
        Entities::PanelBatch::erase(id);
    }
}

void Text::setText(const std::string& text) {
    for (const PanelId id : _panelIds) {
        Entities::PanelBatch::erase(id);
    }
    _panelIds.clear();
    float runningRelativeWidth = 0.0f;
    for (unsigned int i = 0; i < text.length(); ++i) {
        // make a sprite with a texture of the char with the proper font
        std::string charString;
        charString += text[i];
        charString += ".png";
        std::filesystem::path charPath = _fontPath / charString;
        PanelId id = Entities::PanelBatch::insert({_fontPath / charString});
        _panelIds.push_back(id);
        // set the width of the char appropriately
        // we assume all chars have the same height, but width can vary
        Panel& charPanel = Entities::PanelBatch::getRef(id);
        Texture charTexture = charPanel.getTexture();
        float charRelativeWidth = ((float)charTexture.width / (float)charTexture.height);
        runningRelativeWidth += charRelativeWidth;
    }
    setPosition(_position);
}

void Text::setPosition(Point position) {
    _position = position;
    float runningWidth = 0.0f;
    for (unsigned int i = 0; i < _panelIds.size(); ++i) {
        auto& panelRef = Entities::PanelBatch::getRef(_panelIds[i]);
        panelRef.setPosition(Point(runningWidth, 0.0f, 0.0f) + position);
        runningWidth += Entities::PanelBatch::getRef(_panelIds[i]).getSize().x;
    }
};

void Text::setScale(float scale) { _scale = scale; };
} // namespace Eendgine
