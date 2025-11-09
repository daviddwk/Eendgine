#include "Eendgine/camera.hpp"
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
    : m_position(Point(0.0f)), m_size(Scale(1.0f)), m_rotation(0.0f), m_VAO(0), m_VBO(0), m_EBO(0),
      m_currentStripIdx(0), m_flipStrip(false) {
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

Board::~Board() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

Board::Board(Board&& other) noexcept
    : m_position(std::move(other.m_position)), m_size(std::move(other.m_size)),
      m_rotation(std::move(other.m_rotation)), m_VAO(std::move(other.m_VAO)),
      m_VBO(std::move(other.m_VBO)), m_EBO(std::move(other.m_EBO)),
      m_currentStrip(std::move(other.m_currentStrip)),
      m_currentStripIdx(std::move(other.m_currentStripIdx)),
      m_flipStrip(std::move(other.m_flipStrip)), m_stripMap(std::move(other.m_stripMap)),
      m_strips(std::move(other.m_strips)) {
    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_EBO = 0;
};

Board& Board::operator=(Board&& other) noexcept {

    if (&other == this) return *this;

    if (m_VAO != 0) {
        assert(m_VBO != 0);
        assert(m_EBO != 0);
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    } else {
        assert(m_VBO == 0);
        assert(m_EBO == 0);
    }

    m_position = other.m_position;
    m_size = other.m_size;
    m_rotation = other.m_rotation;
    m_VAO = other.m_VAO;
    m_VBO = other.m_VBO;
    m_EBO = other.m_EBO;
    m_currentStrip = other.m_currentStrip;
    m_currentStripIdx = other.m_currentStripIdx;
    m_flipStrip = other.m_flipStrip;
    m_stripMap = other.m_stripMap;
    m_strips = other.m_strips;

    other.m_VAO = 0;
    other.m_VBO = 0;
    other.m_EBO = 0;

    return *this;
};

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
    m_currentStrip = m_stripMap.begin()->first;

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

std::vector<Texture>::size_type Board::getNumTextures() { return m_strips.size(); }

void Board::draw(uint shaderId, Camera3D& camera) {
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

    unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
    unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
    unsigned int transformLoc = glGetUniformLocation(shaderId, "transform");
    unsigned int frameIdxLoc = glGetUniformLocation(shaderId, "frameIdx");
    unsigned int frameLenLoc = glGetUniformLocation(shaderId, "frameLen");
    unsigned int flipLoc = glGetUniformLocation(shaderId, "flip");

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjectionMat()[0][0]);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMat()[0][0]);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

    glUniform1ui(frameIdxLoc, m_currentStripIdx);
    glUniform1ui(frameLenLoc, m_strips[m_stripMap[m_currentStrip]].len);

    glUniform1ui(flipLoc, m_flipStrip);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} // namespace Eendgine
