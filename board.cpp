#include "Eendgine/camera.hpp"
#include "board.hpp"
#include "fatalError.hpp"
#include "textureCache.hpp"
#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.hpp>
#include <print>

namespace Eendgine {

Board::Board(std::filesystem::path path)
    : _position(Point(0.0f)), _size(Scale(1.0f)), _rotation(0.0f), _VAO(0), _VBO(0), _EBO(0),
      _currentTextureIdx(0) {

    std::vector<std::filesystem::path> texturePaths;
    std::filesystem::path spritePath = std::filesystem::path("resources") / path;
    for (const auto& entry : std::filesystem::directory_iterator(spritePath)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".png")) {
            texturePaths.push_back(entry.path());
        }
    }
    setup(texturePaths);
}

Board::~Board() {}

void Board::eraseBuffers() {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
    _VBO = 0;
    _EBO = 0;
    _VAO = 0;
}

void Board::setup(std::vector<std::filesystem::path>& texturePaths) {

    _position = Point(0.0f);
    _size = Scale(1.0f);
    _rotation = 0;

    // sorting them alphabetically, becasue the order they're iterated on
    // is not specified
    std::sort(texturePaths.begin(), texturePaths.end(),
        [](auto a, auto b) { return a.string() < b.string(); });
    for (const auto& t : texturePaths) {
        if (t.has_stem() == false) {
            fatalError("texture: " + t.string() + "has no stem");
        }
        _textureMap[t.stem()] = _textures.size();
        std::print("{}", t.stem().string());
        _textures.push_back(Eendgine::TextureCache::getTexture(t));
    }
    std::print("\n");

    Vertex verticies[4];

    // centered on origin
    // with width and height of 1
    verticies[0].position = Point(0.5f, 0.5f, 0.0f);
    verticies[1].position = Point(0.5f, -0.5f, 0.0f);
    verticies[2].position = Point(-0.5f, -0.5f, 0.0f);
    verticies[3].position = Point(-0.5f, 0.5f, 0.0f);

    verticies[0].color = Color(0.0f, 0.0f, 1.0f, 1.0f);
    verticies[1].color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    verticies[2].color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    verticies[3].color = Color(0.0f, 1.0f, 1.0f, 1.0f);
    //                         w     h
    verticies[0].uv = Point2D(1.0f, 1.0f);
    verticies[1].uv = Point2D(1.0f, 0.0f);
    verticies[2].uv = Point2D(0.0f, 0.0f);
    verticies[3].uv = Point2D(0.0f, 1.0f);

    unsigned int indices[] = {2, 1, 0, 3, 2, 0};

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);

    glGenBuffers(1, &_EBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
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

std::vector<Texture>::size_type Board::getNumTextures() { return _textures.size(); }

void Board::draw(uint shaderId, Camera3D& camera) {
    TransformationMatrix transform = TransformationMatrix(1.0f);
    transform = glm::translate(transform, _position);
    glm::mat3 rot = glm::inverse(glm::mat3(camera.getViewMat()));
    // there must be a cleaner way to do this
    transform = {{rot[0][0], rot[0][1], rot[0][2], transform[0][3]},
        {rot[1][0], rot[1][1], rot[1][2], transform[1][3]},
        {rot[2][0], rot[2][1], rot[2][2], transform[2][3]},
        {transform[3][0], transform[3][1], transform[3][2], transform[3][3]}};
    transform = glm::scale(transform, _size);

    unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjectionMat()[0][0]);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMat()[0][0]);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} // namespace Eendgine
