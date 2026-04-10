#include "board.hpp"

#include "Eendgine/types.hpp"
#include "camera.hpp"
#include "strip.hpp"
#include "texture.hpp"

#include <GLES3/gl3.h>
#include <glm/gtc/type_ptr.hpp>

namespace Eendgine {

Board::Board(std::filesystem::path boardPath)
    : m_position(Point(0.0f)), m_size(Scale(1.0f)), m_rotation(0.0f), m_stripHandler(boardPath) {}

void Board::setPosition(Point position) { m_position = position; };

void Board::setScale(Scale2D scale) { m_size = Scale(scale.x, scale.y, 1.0f); };

void Board::setRotation(Angle angle) { m_rotation = angle; };

void Board::setStrip(std::string strip) { m_stripHandler.setStrip(strip); };

void Board::setStripIdx(unsigned int idx) { m_stripHandler.setStripIdx(idx); };

void Board::setStripFlip(bool flip) { m_stripHandler.setStripFlip(flip); };

void Board::nextStripIdx() { m_stripHandler.nextStripIdx(); };

Point Board::getPosition() { return m_position; };

Scale Board::getSize() { return m_size; };

Angle Board::getRotation() { return m_rotation; };

unsigned int Board::getStripIdx() { return m_stripHandler.getStripIdx(); };

Texture Board::getTexture() const { return m_stripHandler.getTexture(); };

void Board::draw(GLuint shaderId, Camera3D& camera) {
    TransformationMatrix transform = TransformationMatrix(1.0f);
    transform = glm::translate(transform, m_position);

    // TODO the view matrix stuff only needs to be done once per camera
    const glm::mat4 viewMatrix = camera.getViewMat();
    const glm::vec3 boardNormal = glm::vec3(0.0f, 0.0f, -1.0f);
    // get the inverse rotation of the view matrix to make the board an always "facing" plane
    // --
    // facing in the case means facing the same (oppsite) direction as the view matrix
    // it does NOT mean facing the view Matrix's "camera"
    const glm::mat4 viewInverse = glm::inverse(viewMatrix);
    // rotate along the board's normal
    // --
    // this lets us rotate the board, and keeps it facing the camera
    glm::mat3 rotation =
        glm::rotate(viewInverse, glm::radians(m_rotation.getDegrees()), boardNormal);

    // clang-format off
    transform = {
        {rotation[0][0],   rotation[0][1],   rotation[0][2],   transform[0][3]},
        {rotation[1][0],   rotation[1][1],   rotation[1][2],   transform[1][3]},
        {rotation[2][0],   rotation[2][1],   rotation[2][2],   transform[2][3]},
        {transform[3][0],  transform[3][1],  transform[3][2],  transform[3][3]}};
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

    glUniform1ui(frameIdxLoc, m_stripHandler.getStripIdx());
    glUniform1ui(frameLenLoc, m_stripHandler.getStripLen());

    glUniform1ui(flipLoc, m_stripHandler.getStripFlip());

    // we bind the quad once per batch in Entities::draw()
    // glBindVertexArray(Quad::getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0);
}

} // namespace Eendgine
