#include "Eendgine/camera.hpp"
#include "sprite.hpp"
#include "textureCache.hpp"
#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.hpp>

namespace Eendgine {

// can remove the need for two different initializers using templating
Sprite::Sprite(std::filesystem::path texturePath)
    : _position(Point(0.0f)), _size(Scale(1.0f)), _rotation(0.0f), _VAO(0), _textureIdx(0) {
    std::vector<std::filesystem::path> texturePaths{texturePath};
    setup(texturePaths);
}

Sprite::Sprite(std::vector<std::filesystem::path> texturePaths)
    : _position(Point(0.0f)), _size(Scale(1.0f)), _rotation(0.0f), _VAO(0), _textureIdx(0) {
    setup(texturePaths);
}

void Sprite::setup(std::vector<std::filesystem::path>& texturePaths) {

    _position = Point(0.0f);
    _size = Scale(1.0f);
    _rotation = 0;

    for (auto t : texturePaths) {
        _textures.push_back(Eendgine::TextureCache::getTexture(t));
    }
    _textureIdx = 0;

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

    verticies[0].uv = Point2D(1.0f, 1.0f);
    verticies[1].uv = Point2D(1.0f, 0.0f);
    verticies[2].uv = Point2D(0.0f, 0.0f);
    verticies[3].uv = Point2D(0.0f, 1.0f);

    unsigned int indices[] = {0, 1, 2, 0, 2, 3};

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
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

std::vector<Texture>::size_type Sprite::getNumTextures() { return _textures.size(); }

void Sprite::draw(uint shaderId, Camera2D& camera) {
    TransformationMatrix trans = camera.getCameraMatrix(); // glm::mat4(1.0f);

    trans = glm::translate(trans, _position);
    trans = glm::rotate(trans, glm::radians(-_rotation), Point(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, _size);

    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sprite::draw(uint shaderId, Camera3D& camera) {
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
