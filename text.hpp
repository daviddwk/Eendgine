#include "entityBatches.hpp"
#include "types.hpp"
#include <filesystem>
#include <string>
#include <vector>

namespace Eendgine {
class Text {
    public:
        Text(std::filesystem::path fontName, std::string text, Point position, float scale);
        ~Text();

        void setText(const std::string& text);
        void setPosition(Point position);
        void setScale(float scale);

        void clearText();

        Point getPosition() { return _position; };
        float getScale() { return _scale; };

    private:
        std::string _text;
        std::filesystem::path _fontPath;
        std::vector<PanelId> _panelIds;
        Point _position;
        float _scale;
};
} // namespace Eendgine
