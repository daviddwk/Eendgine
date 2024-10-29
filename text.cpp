#include "text.hpp"
#include <filesystem>
#include <stb/stb_image.h>

namespace Eendgine {
Text::Text(std::filesystem::path fontName, std::string text, Point position, float scale)
    : _position(position), _scale(scale), _fontPath("resources/fonts" / fontName) {
    setText(text);
    setPosition(position);
    setScale(scale);
}

Text::~Text() {
    for (const PanelId& id : _panelIds) {
        Entities::PanelBatch::erase(id);
    }
}
void Text::clearText() {
    for (const PanelId id : _panelIds) {
        Entities::PanelBatch::erase(id);
    }
    _panelIds.clear();
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
        Sprite& charSprite = Entities::PanelBatch::getRef(id);
        Texture charTexture = charSprite.getTexture();
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
