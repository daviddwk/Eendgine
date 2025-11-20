#include "primitive.hpp"
#include "vertex.hpp"

namespace Eendgine {

void Quad::construct() {

    assert((m_VAO == 0) && (m_VBO == 0) && (m_EBO == 0));

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

void Quad::destruct() {

    assert((m_VAO != 0) && (m_VBO != 0) && (m_EBO != 0));

    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);

    m_VAO = 0;
    m_VBO = 0;
    m_EBO = 0;
}

GLuint Quad::getVao() {
    assert(m_VAO != 0);
    return m_VAO;
}
} // namespace Eendgine
