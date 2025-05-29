#pragma once

#include "entityBatches.hpp"
#include "types.hpp"
#include <filesystem>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

namespace Eendgine {
class Text {
    public:
        Text(std::filesystem::path fontName, std::string text, Point position, float scale,
            float width);
        ~Text();

        void setText(const std::string& text);
        void setPosition(Point position);
        void setScale(float scale);

        Point getPosition() { return _position; };
        float getScale() { return _scale; };

    private:
        void updateText();
        std::string _text;
        float _width;
        std::filesystem::path _fontPath;
        std::vector<PanelId> _panelIds;
        Point _position;
        float _scale;
        Texture _texture;
        std::array<std::optional<std::tuple<unsigned int, unsigned int>>,
            std::numeric_limits<char>::max() + 1>
            _charColumns;
};
} // namespace Eendgine
