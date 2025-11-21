#include "Eendgine/camera.hpp"
#include "Eendgine/primitive.hpp"
#include "Eendgine/texture.hpp"
#include "board.hpp"
#include "fatalError.hpp"
#include "textureCache.hpp"
#include <GLES3/gl3.h>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <json/json.h>

namespace Eendgine {

Board::Board(std::filesystem::path path)
    : m_position(Point(0.0f)), m_size(Scale(1.0f)), m_rotation(0.0f), m_currentStripIdx(0),
      m_flipStrip(false) {
    std::filesystem::path basePath = std::filesystem::path("resources") / path;
    std::filesystem::path metadataPath = basePath / "metadata.json";
    std::vector<std::filesystem::path> texturePaths;
    for (const auto& entry : std::filesystem::directory_iterator(basePath)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".png")) {
            texturePaths.push_back(entry.path());
        }
    }
    setup(texturePaths, metadataPath);
}

void Board::setStrip(std::string strip) {
    assert(m_stripMap.find(strip) != m_stripMap.end());
    m_currentStrip = strip;
    m_currentStripIdx = 0;
};

void Board::setStripIdx(unsigned int idx) {
    m_currentStripIdx = idx % m_strips[m_stripMap[m_currentStrip]].len;
};

void Board::nextStripIdx() {
    m_currentStripIdx = (m_currentStripIdx + 1) % m_strips[m_stripMap[m_currentStrip]].len;
};

void Board::setFlip(bool flip) { m_flipStrip = flip; };

void Board::setPosition(Point position) { m_position = position; };

void Board::setScale(Scale2D scale) { m_size = Scale(scale.x, scale.y, 1.0f); };

void Board::setRotation(float r) { m_rotation = r; };

std::vector<Strip>::size_type Board::getStripLen() {
    return m_strips[m_stripMap[m_currentStrip]].len;
};

unsigned int Board::getStripIdx() { return m_currentStripIdx; };

Point Board::getPosition() { return m_position; };

Scale Board::getSize() { return m_size; };

float Board::getRotation() { return m_rotation; };

Texture Board::getTexture() const { return m_strips.at(m_stripMap.at(m_currentStrip)).texture; };

void Board::setup(
    std::vector<std::filesystem::path>& texturePaths, std::filesystem::path& metadataPath) {

    m_position = Point(0.0f);
    m_size = Scale(1.0f);
    m_rotation = 0;

    // sorting them alphabetically, becasue the order they're iterated on
    // is not specified
    std::sort(texturePaths.begin(), texturePaths.end(), [](auto a, auto b) {
        return a.string() < b.string();
    });
    for (const auto& t : texturePaths) {
        if (t.has_stem() == false) {
            fatalError("texture: " + t.string() + "has no stem");
        }
        m_stripMap[t.stem()] = m_strips.size();
        m_strips.push_back((Strip){TextureCache::getTexture(t), 1}); // default to 1
    }
    assert(m_stripMap.size() > 0);

    auto [stripName, stripIdx] = *m_stripMap.begin();
    m_currentStrip = stripName;

    Json::Value rootJson;
    std::ifstream metadata(metadataPath);
    if (metadata.is_open()) {
        try {
            metadata >> rootJson;
        } catch (...) {
            fatalError("improper json: " + metadataPath.string());
        }
        for (const auto& t : texturePaths) {
            if (rootJson[t.stem()].isUInt()) {
                m_strips[m_stripMap[t.stem()]].len = rootJson[t.stem()].asUInt();
            }
        }
    }
}

std::vector<Texture>::size_type Board::getNumTextures() { return m_strips.size(); }

void Board::draw(GLuint shaderId, Camera3D& camera) {
    TransformationMatrix transform = TransformationMatrix(1.0f);
    transform = glm::translate(transform, m_position);
    glm::mat3 rot = glm::inverse(glm::mat3(camera.getViewMat()));
    // there must be a cleaner way to do this
    // clang-format off
    transform = {
        {rot[0][0],       rot[0][1],       rot[0][2],       transform[0][3]},
        {rot[1][0],       rot[1][1],       rot[1][2],       transform[1][3]},
        {rot[2][0],       rot[2][1],       rot[2][2],       transform[2][3]},
        {transform[3][0], transform[3][1], transform[3][2], transform[3][3]}};
    // clang-format on
    transform = glm::scale(transform, m_size);

    GLint projectionLoc = glGetUniformLocation(shaderId, "projection");
    GLint viewLoc = glGetUniformLocation(shaderId, "view");
    GLint transformLoc = glGetUniformLocation(shaderId, "transform");
    GLint frameIdxLoc = glGetUniformLocation(shaderId, "frameIdx");
    GLint frameLenLoc = glGetUniformLocation(shaderId, "frameLen");
    GLint flipLoc = glGetUniformLocation(shaderId, "flip");

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjectionMat()[0][0]);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMat()[0][0]);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

    glUniform1ui(frameIdxLoc, m_currentStripIdx);
    glUniform1ui(frameLenLoc, m_strips[m_stripMap[m_currentStrip]].len);

    glUniform1ui(flipLoc, m_flipStrip);

    // we bind the quad once per batch in Entities::draw()
    // glBindVertexArray(Quad::getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);
}

} // namespace Eendgine
