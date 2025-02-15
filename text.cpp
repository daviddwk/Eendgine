#include "fatalError.hpp"
#include "text.hpp"
#include <filesystem>
#include <fstream>
#include <json/json.h>
#include <limits>
#include <optional>
#include <stb/stb_image.h>

std::array possibleChars = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\'', '"', '.', ',', '?', '!', ':'};

namespace Eendgine {
Text::Text(std::filesystem::path fontName, std::string text, Point position, float scale)
    : _text(text), _fontPath(std::filesystem::path("fonts") / fontName), _position(position),
      _scale(scale), _charColumns({std::nullopt}) {

    _texture = loadTexture("resources" / _fontPath / "font.png");

    // open json
    Json::Value root;
    std::filesystem::path metadataPath = "resources" / _fontPath / "metadata.json";
    std::ifstream metadata(metadataPath);
    if (!metadata.is_open()) {
        fatalError("could not open: " + metadataPath.string());
    }
    try {
        metadata >> root;
    } catch (...) {
        fatalError("improper json: " + metadataPath.string());
    }

    // ' ' to '~' see https://www.ascii-code.com/
    for (char ch = 32; ch < 127; ++ch) {
        Json::Value jsonChar = root[std::format("{}", ch)];
        if (!jsonChar.isArray())
            continue;
        const unsigned int firstColumn = jsonChar[0].asUInt();
        const unsigned int lastColumn = jsonChar[1].asUInt();

        bool first_after_last = firstColumn > lastColumn;
        bool exceeded_max = (firstColumn >= _texture.width) || (lastColumn >= _texture.width);

        if (!first_after_last && !exceeded_max) {
            _charColumns[ch] = std::tie(firstColumn, lastColumn);
        } else {
            fatalError("malformatted font metadat\n");
            // print error and move on
        }
    }

    // this should point to a folder with just font pngs?
    // need to unwrap optional here
    for (size_t char_idx = 0; char_idx < _text.length(); ++char_idx) {
        _panelIds.push_back(Entities::PanelBatch::insert(_fontPath));
    }
    updateText();
}

Text::~Text() {
    for (const PanelId& id : _panelIds) {
        Entities::PanelBatch::erase(id);
    }
}

void Text::setText(const std::string& text) {
    if (_text == text)
        return;

    _text = text;

    for (const PanelId& id : _panelIds) {
        Entities::PanelBatch::erase(id);
    }
    _panelIds.clear();
    for (size_t char_idx = 0; char_idx < _text.length(); ++char_idx) {
        _panelIds.push_back(Entities::PanelBatch::insert(_fontPath));
    }
    updateText();
}

void Text::setPosition(Point position) {

    _position = position;
    updateText();
}

void Text::setScale(float scale) {

    _scale = scale;
    updateText();
}

void Text::updateText() {
    float horizontal = 0.0f;
    for (size_t char_idx = 0; char_idx < _text.length(); ++char_idx) {
        if (!_charColumns[_text[char_idx]].has_value())
            continue;

        unsigned int firstColumn = std::get<0>(_charColumns[_text[char_idx]].value());
        unsigned int lastColumn = std::get<1>(_charColumns[_text[char_idx]].value());
        unsigned int charWidth = (lastColumn - firstColumn) + 1;

        Panel& panelRef = Entities::PanelBatch::getRef(_panelIds[char_idx]);

        panelRef.setPosition(Point(_position.x + horizontal, _position.y, _position.z));
        horizontal += ((float)charWidth / (float)_texture.height) * _scale;

        panelRef.setScale(Scale2D(_scale * ((float)charWidth / (float)_texture.height), _scale));
        Point2D upperLeft(firstColumn, 0.0f);
        Point2D lowerRight(lastColumn + 1.0f, _texture.height);

        panelRef.cropTexture(
            Point2D(firstColumn, 0.0f), Point2D(lastColumn + 1.0f, _texture.height));
    }
}

} // namespace Eendgine
