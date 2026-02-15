#include <assert.h>

#include "fatalError.hpp"
#include "shaders.hpp"

#include "screen.hpp"

namespace Eendgine {

Screen::Screen(int width, int height) {
    m_width = width;
    m_height = height;
    /*
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_screenTriVerts), &m_screenTriVerts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glGenFramebuffers(1, &m_FB);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FB);

    glGenTextures(1, &m_textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        m_textureColorBuffer,
        0);

    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        fatalError("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Screen::~Screen() {
    // TODO somthing here I'm sure
}

void Screen::construct(int width, int height) {
    assert(_instance == nullptr);
    _instance = new Screen(width, height);
}

void Screen::destruct() {
    assert(_instance != nullptr);
    delete _instance;
    _instance = nullptr;
}

Screen& Screen::get() {
    assert(_instance != nullptr);
    return *_instance;
}

void Screen::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_FB);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::render() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Shaders::get().getShader(Shader::screen).use();
    glBindVertexArray(m_VAO);
    glUniform1i(
        glGetUniformLocation(
            Shaders::get().getShader(Shader::screen).getProgramID(),
            "screenTexture"),
        0);
    glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);

    unsigned int heightLoc =
        glGetUniformLocation(Shaders::get().getShader(Shader::screen).getProgramID(), "height");
    unsigned int widthLoc =
        glGetUniformLocation(Shaders::get().getShader(Shader::screen).getProgramID(), "width");
    glUniform1i(heightLoc, m_height);
    glUniform1i(widthLoc, m_width);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
} // namespace Eendgine
