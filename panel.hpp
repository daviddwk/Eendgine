#pragma once
#include "camera.hpp"
#include "strip.hpp"
#include "types.hpp"
#include <filesystem>
#include <map>
#include <vector>

namespace Eendgine {
// TODO combine these into one again
class Panel {
    public:
        Panel(std::filesystem::path path);
        ~Panel();

        Panel(const Panel& other) = delete;
        Panel& operator=(const Panel& other) = delete;

        Panel(Panel&& other) noexcept;
        Panel& operator=(Panel&& other) noexcept;

        enum class MouseStatus {
            none,
            hover,
            click,
        };

        void setTexture(std::string texture);
        void setPosition(Point position);
        void setScale(Scale2D scale);
        void setRotation(float r);

        std::string getTextureName();
        Point getPosition();
        Scale getScale();
        float getRotation();
        Texture getTexture() const;

        void cropTexture(Point2D upperLeft, Point2D lowerRight);

        MouseStatus isClicked();

        void draw(GLuint shaderId, Camera2D& camera);

    private:
        void setup(std::vector<std::filesystem::path>& texturePaths);
        Point m_position;
        Scale m_scale;
        float m_rotation;
        GLuint m_VAO, m_VBO, m_EBO;
        std::string m_currentTexture;
        std::map<std::string, Texture> m_textures;
};
} // namespace Eendgine
