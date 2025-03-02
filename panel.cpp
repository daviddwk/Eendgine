#include <print>

#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "fatalError.hpp"
#include "panel.hpp"
#include "textureCache.hpp"

namespace Eendgine {

// can remove the need for two different initializers using templating
Panel::Panel(std::filesystem::path path)
    : position(Point(0.0f)), scale(Scale(1.0f)), rotation(0.0f), VAO(0), VBO(0), EBO(0),
      currentTexture("") {

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

void Panel::eraseBuffers() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    VBO = 0;
    EBO = 0;
    VAO = 0;
}

void Panel::setup(std::vector<std::filesystem::path>& texturePaths) {

    position = Point(0.0f);
    scale = Scale(1.0f);
    rotation = 0;

    for (const auto& t : texturePaths) {
        if (t.has_stem() == false) {
            fatalError("texture: " + t.string() + "has no stem");
        }
        textures[t.stem()] = Eendgine::TextureCache::getTexture(t);
    }
    currentTexture = textures.begin()->first;

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

    verticies[0].uv = Point2D(1.0f, 1.0f);
    verticies[1].uv = Point2D(1.0f, 0.0f);
    verticies[2].uv = Point2D(0.0f, 0.0f);
    verticies[3].uv = Point2D(0.0f, 1.0f);

    unsigned int indices[] = {0, 1, 2, 0, 2, 3};

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

void Panel::cropTexture(Point2D upperLeft, Point2D lowerRight) {
    Vertex verticies[4];
    float textureHeight = textures[currentTexture].height;
    float textureWidth = textures[currentTexture].width;

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

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Vertex), verticies);

    //_textures[_currentTexture].height;
}

void Panel::setTexture(std::string textureName) {
    if (textures.contains(textureName)) {
        currentTexture = textureName;
    } else {
        std::print("WARNING: textureName {} does not exsist", textureName);
    }
}

std::vector<Texture>::size_type Panel::getNumTextures() { return textures.size(); }

void Panel::draw(uint shaderId, Camera2D& camera) {
    TransformationMatrix trans = camera.getCameraMatrix(); // glm::mat4(1.0f);
    Scale2D cameraDims = camera.getDimensions();

    trans = glm::translate(trans, glm::vec3(-(cameraDims.x / 2.0f), (cameraDims.y / 2.0f), 0.0f));
    trans = glm::translate(trans, Point(position.x, -position.y, position.z));
    trans = glm::rotate(trans, glm::radians(-rotation), Point(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, Scale(scale.x, scale.y, 0.0f));

    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
} // namespace Eendgine
