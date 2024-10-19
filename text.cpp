#include "text.hpp"
#include "info.hpp"
#include <filesystem>
#include <stb/stb_image.h>

namespace Eendgine {
Text::Text(std::filesystem::path fontName, unsigned int scale, std::string string)
    : _position(glm::vec3(0.0f)), _size(glm::vec3(1.0f)), _panelIds(std::vector<PanelId>()) {
    const std::filesystem::path fontPath = "resources/fonts" / fontName;
    float runningRelativeWidth = 0;

    for (unsigned int i = 0; i < string.length(); ++i) {

        Info::registerInt("char" + std::to_string(i), 0);

        // make a sprite with a texture of the char with the proper font
        std::string charString;
        charString += string[i];
        charString += ".png";
        std::filesystem::path charPath = fontPath / charString;
        PanelId id = Entities::PanelBatch::insert({fontPath / charString});
        _panelIds.push_back(id);
        Info::registerInt("char" + std::to_string(string[i]), id);
        Info::updateInt("char" + std::to_string(string[i]), id);
        // set the width of the char appropriately
        // we assume all chars have the same height, but width can vary
        Sprite &charSprite = Entities::PanelBatch::getRef(id);
        Texture charTexture = charSprite.getTexture();
        float charRelativeWidth = ((float)charTexture.width / (float)charTexture.height);
        charSprite.setScale(scale * charRelativeWidth, scale * 1);
        charSprite.setPosition(glm::vec3(scale * runningRelativeWidth, 0.0f, 0.0f));

        // set position appropriately
        runningRelativeWidth += charRelativeWidth;
    }
}

Text::~Text() {
    for (const PanelId &id : _panelIds) {
        Entities::PanelBatch::erase(id);
    }
}
} // namespace Eendgine
