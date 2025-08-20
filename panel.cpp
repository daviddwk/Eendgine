#include <print>

#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "fatalError.hpp"
#include "inputManager.hpp"
#include "textureCache.hpp"
#include "vertex.hpp"

#include "panel.hpp"

namespace Eendgine {

// can remove the need for two different initializers using templating
Panel::Panel(std::filesystem::path path)
    : m_position(Point(0.0f)), m_scale(Scale(1.0f)), m_rotation(0.0f), m_VAO(0), m_VBO(0), m_EBO(0),
      m_currentTexture("") {

    std::vector<std::filesystem::path> texturePaths;
    std::filesystem::path spritePath = std::filesystem::path("resources") / path;
    for (const auto& entry : std::filesystem::directory_iterator(spritePath)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".png")) {
            texturePaths.push_back(entry.path());
        }
    }
    setup(texturePaths);
}

Panel::~Panel() {}

void Panel::setTexture(std::string texture) { m_currentTexture = texture; };
void Panel::setPosition(Point position) { m_position = Point{position.x, -position.y, position.z}; };
void Panel::setScale(Scale2D scale) { m_scale = Scale(scale.x, scale.y, 1.0f); };
void Panel::setRotation(float rotation) { m_rotation = rotation; };

std::string Panel::getTextureName() { return m_currentTexture; };
Point Panel::getPosition() { return Point{m_position.x, -m_position.y, m_position.z}; };
Scale Panel::getScale() { return m_scale; };
float Panel::getRotation() { return m_rotation; };
Texture Panel::getTexture() { return m_textures[m_currentTexture]; };

void Panel::cropTexture(Point2D upperLeft, Point2D lowerRight) {
    Vertex verticies[4];
    float textureHeight = m_textures[m_currentTexture].height;
    float textureWidth = m_textures[m_currentTexture].width;

    // centered on origin
    // with width and height of 1
    // TODO make this array a shared constant
    verticies[0].position = Point(1.0f, -1.0f, 0.0f);
    verticies[1].position = Point(1.0f, 0.0f, 0.0f);
    verticies[2].position = Point(0.0f, 0.0f, 0.0f);
    verticies[3].position = Point(0.0f, -1.0f, 0.0f);

    verticies[0].color = Color(0.0f, 0.0f, 1.0f, 1.0f);
    verticies[1].color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    verticies[2].color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    verticies[3].color = Color(0.0f, 1.0f, 1.0f, 1.0f);

    verticies[0].uv =
        Point2D(lowerRight.x / textureWidth, (textureHeight - lowerRight.y) / textureHeight);
    verticies[1].uv =
        Point2D(lowerRight.x / textureWidth, (textureHeight - upperLeft.y) / textureHeight);
    verticies[2].uv =
        Point2D(upperLeft.x / textureWidth, (textureHeight - upperLeft.y) / textureHeight);
    verticies[3].uv =
        Point2D(upperLeft.x / textureWidth, (textureHeight - lowerRight.y) / textureHeight);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Vertex), verticies);

    //_textures[_currentTexture].height;
}

void Panel::eraseBuffers() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    m_VBO = 0;
    m_EBO = 0;
    m_VAO = 0;
}

Panel::MouseStatus Panel::isClicked() {
    int mouseX = InputManager::get().getMouseX();
    int mouseY = InputManager::get().getMouseY();
    bool click = InputManager::get().getLeftClick();

    bool inXBounds = mouseX >= m_position.x && mouseX <= (m_position.x + m_scale.x);
    bool inYBounds = mouseY >= -m_position.y && mouseY <= (-m_position.y + m_scale.y);
    if (inXBounds && inYBounds) {
        if (click) {
            return MouseStatus::CLICK;
        }
        return MouseStatus::HOVER;
    }
    return MouseStatus::NONE;
}

void Panel::setup(std::vector<std::filesystem::path>& texturePaths) {

    m_position = Point(0.0f);
    m_scale = Scale(1.0f);
    m_rotation = 0;

    for (const auto& t : texturePaths) {
        if (t.has_stem() == false) {
            fatalError("texture: " + t.string() + "has no stem");
        }
        m_textures[t.stem()] = Eendgine::TextureCache::getTexture(t);
    }
    m_currentTexture = m_textures.begin()->first;

    Vertex verticies[4];

    // centered on origin
    // with width and height of 1
    verticies[0].position = Point(1.0f, -1.0f, 0.0f);
    verticies[1].position = Point(1.0f, 0.0f, 0.0f);
    verticies[2].position = Point(0.0f, 0.0f, 0.0f);
    verticies[3].position = Point(0.0f, -1.0f, 0.0f);

    verticies[0].color = Color(0.0f, 0.0f, 1.0f, 1.0f);
    verticies[1].color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    verticies[2].color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    verticies[3].color = Color(0.0f, 1.0f, 1.0f, 1.0f);

    verticies[0].uv = Point2D(1.0f, -1.0f);
    verticies[1].uv = Point2D(1.0f, 0.0f);
    verticies[2].uv = Point2D(0.0f, 0.0f);
    verticies[3].uv = Point2D(0.0f, -1.0f);

    unsigned int indices[] = {0, 1, 2, 0, 2, 3};

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);

    glGenBuffers(1, &m_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);
}

void Panel::draw(uint shaderId, Camera2D& camera) {
    TransformationMatrix trans = camera.getCameraMatrix(); // glm::mat4(1.0f);
    Scale2D cameraDims = camera.getDimensions();

    trans = glm::translate(trans, glm::vec3(-(cameraDims.x / 2.0f), (cameraDims.y / 2.0f), 0.0f));
    trans = glm::translate(trans, m_position);
    trans = glm::rotate(trans, glm::radians(-m_rotation), Point(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, m_scale);

    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
} // namespace Eendgine
